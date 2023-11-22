#pragma once
#include <cstdlib> 
#include <cstdio> 
#include <cstring> 
#include <ctime> 
#include <cmath> 
#include <algorithm> 
#include <mpi.h> 
#include <iostream>
#include <string>

#include "../Array.h"

enum SplitMode { KEEP_FIRST_HALF, KEEP_SECOND_HALF };

class HPC
{
public:
	HPC(int argc, char* argv[]);
	~HPC();

	int get_process_rank() const;
	int get_process_num() const;
	
	Array& get_array();
	void set_array(const Array& array);
	void parallel_bubble_sort();

private:
	void array_distribution();
	void array_collection();
	void exchange_values(int dual_rank, double* dual_values, int dual_block_size);

	int process_num = 0;
	int process_rank = -1;

	Array array;

	double* process_values = nullptr;
	int size = 0;
	int block_size = 0;

	void log(std::string message);
};

