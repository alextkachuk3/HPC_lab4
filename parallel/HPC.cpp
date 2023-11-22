#include "HPC.h"

HPC::HPC(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &process_num);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	setvbuf(stdout, 0, _IONBF, 0);
}

HPC::~HPC()
{
	MPI_Finalize();
}

int HPC::get_process_rank() const
{
	return process_rank;
}

int HPC::get_process_num() const
{
	return process_num;
}

Array& HPC::get_array()
{
	return array;
}

void HPC::set_array(const Array& array)
{
	this->array = array;
}

void HPC::parallel_bubble_sort()
{
	if (process_rank == 0)
	{
		size = array.get_size();
	}

	MPI_Bcast(&size, 1, MPI_INT, 0, MPI_COMM_WORLD);

	int rest_data = size;
	for (int i = 0; i < process_rank; i++)
		rest_data -= rest_data / (process_num - i);
	block_size = rest_data / (process_num - process_rank);
	process_values = new double[block_size];

	array_distribution();

	Array::serial_bubble_sort(process_values, block_size);

	int offset;
	SplitMode split_mode;
	for (int i = 0; i < process_num; i++) {
		if ((i % 2) == 1) {
			if ((process_rank % 2) == 1) {
				offset = 1;
				split_mode = KEEP_FIRST_HALF;
			}
			else {
				offset = -1;
				split_mode = KEEP_SECOND_HALF;
			}
		}
		else {
			if ((process_rank % 2) == 1) {
				offset = -1;
				split_mode = KEEP_SECOND_HALF;
			}
			else {
				offset = 1;
				split_mode = KEEP_FIRST_HALF;
			}
		}

		if ((process_rank == process_num - 1) && (offset == 1)) continue;
		if ((process_rank == 0) && (offset == -1)) continue;
		MPI_Status status;
		int dual_block_size;
		MPI_Sendrecv(&block_size, 1, MPI_INT, process_rank + offset, 0, &dual_block_size, 1, MPI_INT, process_rank + offset, 0, MPI_COMM_WORLD, &status);
		double* dual_data = new double[dual_block_size];
		double* merged_data = new double[block_size + dual_block_size];

		exchange_values(process_rank + offset, dual_data, dual_block_size);

		std::merge(process_values, process_values + block_size, dual_data, dual_data +
			dual_block_size, merged_data);

		if (split_mode == KEEP_FIRST_HALF)
			std::copy(merged_data, merged_data + block_size, process_values);
		else
			std::copy(merged_data + block_size, merged_data + block_size + dual_block_size, process_values);

		delete[] dual_data;
		delete[] merged_data;
	}



	MPI_Barrier(MPI_COMM_WORLD);

	array_collection();

	delete[] process_values;
}

void HPC::array_distribution()
{
	int* send_ind = new int[process_num];
	int* send_num = new int[process_num];
	int rest_data = size;
	int current_size = size / process_num;
	send_num[0] = current_size;
	send_ind[0] = 0;
	for (int i = 1; i < process_num; i++) {
		rest_data -= current_size;
		current_size = rest_data / (process_num - i);
		send_num[i] = current_size;
		send_ind[i] = send_ind[i - 1] + send_num[i - 1];
	}
	MPI_Scatterv(array.get_values(), send_num, send_ind, MPI_DOUBLE, process_values,
		send_num[process_rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);

	delete[] send_num;
	delete[] send_ind;
}

void HPC::array_collection()
{
	int* receive_num = new int[process_num];
	int* receive_ind = new int[process_num];
	int rest_data = size;
	receive_ind[0] = 0;

	receive_num[0] = size / process_num;
	for (int i = 1; i < process_num; i++) {
		rest_data -= receive_num[i - 1];
		receive_num[i] = rest_data / (process_num - i);
		receive_ind[i] = receive_ind[i - 1] + receive_num[i - 1];
	}
	MPI_Gatherv(process_values, block_size, MPI_DOUBLE, array.get_values(),
		receive_num, receive_ind, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	delete[] receive_num;
	delete[] receive_ind;
}

void HPC::exchange_values(int dual_rank, double* dual_values, int dual_block_size)
{
	MPI_Status status;
	MPI_Sendrecv(process_values, block_size, MPI_DOUBLE, dual_rank, 0, dual_values, dual_block_size, MPI_DOUBLE, dual_rank, 0, MPI_COMM_WORLD, &status);
}

void HPC::log(std::string message)
{
	std::cout << ("Process rank:" + std::to_string(process_rank) + " " + message + "\n");
	MPI_Barrier(MPI_COMM_WORLD);
}
