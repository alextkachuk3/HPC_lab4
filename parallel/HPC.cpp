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
	if (process_values != nullptr)
	{
		delete[] process_values;
	}
}

int HPC::get_process_rank() const
{
	return process_rank;
}

int HPC::get_process_num() const
{
	return process_num;
}

Array HPC::get_array()
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

	log("Size: " + std::to_string(size));
}

void HPC::log(std::string message)
{
	std::cout << ("Process rank:" + std::to_string(process_rank) + " " + message + "\n");
	MPI_Barrier(MPI_COMM_WORLD);
}
