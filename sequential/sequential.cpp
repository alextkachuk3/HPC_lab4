#include <cstdlib> 
#include <iostream>
#include "../Array.h"

int main(int argc, char* argv[]) {
	srand(clock());

	Array array(15);
	array.random_data_initialization();

	std::cout << array;

	return 0;
}