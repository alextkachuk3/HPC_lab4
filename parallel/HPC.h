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

private:
	int process_num;
	int process_rank;

	double* process_rows;
	double* process_result;

	void log(std::string message);
};

