#include <iostream>
#include <iomanip>
#include <chrono>

#include "HPC.h"

bool print_values = false;
bool evaluation_test = false;

void test_sorting(HPC& hpc, const int& size)
{
	std::cout << std::endl << "Array size: " << size << std::endl << std::endl;

	Array array(size);
	array.random_data_initialization();

	if (print_values)
	{
		std::cout << "Array: " << std::endl << array << std::endl;
	}

	auto start = std::chrono::high_resolution_clock::now();

	hpc;

	auto finish = std::chrono::high_resolution_clock::now();

	if (print_values)
	{
		std::cout << "Sorted array: " << std::endl << array;
	}

	double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * 1.0e-9;

	std::cout << "Time of execution parallel sorting: " << std::fixed << std::setprecision(8) << duration << std::setprecision(4) << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
	srand(clock());

	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-p") == 0)
		{
			print_values = true;
		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			evaluation_test = true;
		}
	}

	HPC hpc(argc, argv);

	int evaluation_sizes[] = { 10, 100, 10000, 20000, 30000, 40000, 50000 };

	if (hpc.get_process_rank() == 0)
	{
		if (evaluation_test)
		{
			for (int i = 0; i < sizeof(evaluation_sizes) / sizeof(int); i++)
			{
				test_sorting(hpc, evaluation_sizes[i]);
			}
			return 0;
		}
		else
		{
			std::cout << "Enter size of matrix:";

			int size;
			std::cin >> size;

			test_sorting(hpc, size);
			return 0;
		}
	}
	else
	{
		if (evaluation_test)
		{
			for (int i = 0; i < sizeof(evaluation_sizes) / sizeof(int); i++)
			{
				hpc;
			}
		}
		else
		{
			hpc;
		}
	}

	return 0;
}
