#include "matrix.h"

matrix::matrix(size_t rows, size_t cols)
{
	this->rows = rows;
	this->cols = cols;
	M.resize(rows);
	for (auto row = M.begin(); row != M.end(); ++row) row->resize(cols);
}

matrix::matrix(){}

void matrix::fill_val(double val, size_t rows, size_t cols)
{
	M.resize(rows);
	for (size_t i = 0; i < rows; ++i) M[i].resize(cols);
	this->rows = rows;
	this->cols = cols;
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j) M[i][j] = val;
	}
}