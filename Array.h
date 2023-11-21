#pragma once

#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <ostream>
#include <iomanip>

class Array
{
public:
	Array(const int& size);
	~Array();

	Array(const Array& other);

	void serial_std_sort();
	void serial_bubble_sort();

	void random_data_initialization();

	double& operator[](const size_t& index) const;
	friend std::ostream& operator<< (std::ostream& out, const Array& array);
private:
	double* values;
	const int size;

	static const double random_data_multiplier;
	static const int output_field_width;
};

