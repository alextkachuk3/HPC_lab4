#include "Array.h"

const double Array::random_data_multiplier = 1000.0;
const int Array::output_field_width = 10;

Array::Array() : size(0)
{
	values = new double[size] {};
}

Array::Array(const int& size)
{
	this->size = size;
	values = new double[size] {};
}

Array::~Array()
{
	delete[] values;
}

Array::Array(const Array& other)
{
	size = other.size;
	values = new double[size];
	memcpy_s(values, size * sizeof(double), other.values, other.size * sizeof(double));
}

double* Array::get_values()
{
	return values;
}

int Array::get_size() const
{
	return size;
}

void Array::serial_std_sort()
{
	std::sort(values, values + size);
}

void Array::serial_bubble_sort()
{
	serial_bubble_sort(values, size);
}

void Array::serial_bubble_sort(double*& values, const int& size)
{
	double temp;
	for (int i = 1; i < size; i++)
	{
		for (int j = 0; j < size - i; j++)
		{
			if (values[j] > values[j + 1]) {
				temp = values[j];
				values[j] = values[j + 1];
				values[j + 1] = temp;
			}
		}
	}
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

bool Array::operator==(const Array& other)
{
	if (this->size != other.size)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->values[i] != other.values[i])
			{
				return false;
			}
		}
		return true;
	}
}

Array& Array::operator=(const Array& other)
{
	if (this == &other)
	{
		return *this;
	}

	size = other.size;
	values = new double[size];
	memcpy_s(values, size * sizeof(double), other.values, other.size * sizeof(double));
	return *this;
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
