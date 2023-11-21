#pragma once
#include <mpi.h>
#include <iostream>
#include <string>

#include "../Array.h"

class HPC
{
public:
	HPC(int argc, char* argv[]);
	~HPC();

	int get_process_rank() const;
	int get_process_num() const;
	
	Array get_array();
	void set_array(const Array& array);
	void parallel_bubble_sort();

private:
	int process_num;
	int process_rank;

	Array array;

	double* process_values = nullptr;
	int size = 0;
	int block_size = 0;

	void log(std::string message);
};

