#ifndef MATRIX
#define MATRIX

#include <vector>
#include <iostream>

class matrix
{
public:
	size_t rows, cols;
	std::vector<std::vector<double>> M;

	matrix(size_t rows, size_t cols);
	matrix();
	void fill_val(double val, size_t rows, size_t cols);
};

#endif//MATRIX
