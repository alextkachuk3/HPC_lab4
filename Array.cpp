#include "Array.h"

const double Array::random_data_multiplier = 1000.0;
const int Array::output_field_width = 10;

Array::Array(const int& size) : size(size)
{
	values = new double[size] {};
}

Array::~Array()
{
	delete[] values;
}

Array::Array(const Array& other) : size(other.size)
{
	values = new double[size];
	memcpy_s(values, size * sizeof(double), other.values, other.size * sizeof(double));
}

void Array::random_data_initialization()
{
	for (int i = 0; i < size; i++)
	{
		values[i] = double(rand()) / RAND_MAX * random_data_multiplier;
	}
}

double& Array::operator[](const size_t& index) const
{
	return values[index];
}

std::ostream& operator<<(std::ostream& out, const Array& array)
{
	for (int i = 0; i < array.size; i++)
	{
		out << std::setw(array.output_field_width) << array[i];;
	}

	out << std::endl;

	return out;
}
