#include <iostream>
#include <iomanip>
#include <chrono>

#include "../Array.h"

bool print_values = false;
bool evaluation_test = false;

enum SortType
{
	STD,
	BUBBLE
};

double test_sorting(Array array, SortType sort_type)
{
	auto start = std::chrono::high_resolution_clock::now();

	switch (sort_type)
	{
	case STD:
		array.serial_std_sort();		
		break;
	case BUBBLE:
		array.serial_bubble_sort();
		break;
	}

	auto finish = std::chrono::high_resolution_clock::now();

	if (print_values)
	{
		std::cout << "Sorted array: " << std::endl << array;
	}

	return std::chrono::duration_cast<std::chrono::nanoseconds>(finish - start).count() * 1.0e-9;
}

void test_sorting(const int& size)
{
	std::cout << std::endl << "Array size: " << size << std::endl << std::endl;

	Array array(size);
	array.random_data_initialization();

	if (print_values)
	{
		std::cout << "Array: " << std::endl << array << std::endl;
	}

	double duration = test_sorting(array, SortType::STD);

	std::cout << "Time of execution serial standart sorting: " << std::fixed << std::setprecision(8) << duration << std::setprecision(4) << std::endl << std::endl;

	duration = test_sorting(array, SortType::BUBBLE);
	
	std::cout << "Time of execution serial bubble sorting: " << std::fixed << std::setprecision(8) << duration << std::setprecision(4) << std::endl << std::endl;
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

	if (evaluation_test)
	{
		int evaluation_sizes[] = { 10, 100, 10000, 20000, 30000, 40000, 50000 };

		for (int i = 0; i < sizeof(evaluation_sizes) / sizeof(int); i++)
		{
			test_sorting(evaluation_sizes[i]);
		}
		return 0;
	}
	
	std::cout << "Enter size of matrix:";

	int size;
	std::cin >> size;

	test_sorting(size);

	return 0;
}
