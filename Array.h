#pragma once

#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <ostream>
#include <iomanip>

class Array
{
public:
	Array();
	Array(const int& size);	
	~Array();

	Array(const Array& other);

	double* get_values() const;
	int get_size() const;

	void serial_std_sort();
	void serial_bubble_sort();

	void random_data_initialization();

	double& operator[](const size_t& index) const;
	bool operator==(const Array& other);
	Array& operator=(const Array& other);
	friend std::ostream& operator<< (std::ostream& out, const Array& array);
private:
	double* values;
	int size;

	static const double random_data_multiplier;
	static const int output_field_width;
};

