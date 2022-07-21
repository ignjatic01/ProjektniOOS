#include "Matrix.h"

Matrix::Matrix() : arr(nullptr), row(0), col(0)
{
}

Matrix::Matrix(int* arr, int row, int col) : row(row), col(col), arr(new int[row*col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->arr[i * col + j] = arr[i * col + j];
		}
	}
}

Matrix::Matrix(int row, int col) : row(row), col(col), arr(new int[row * col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			this->arr[i * col + j] = 0;
		}
	}
}

Matrix::Matrix(const Matrix& other) : row(other.row), col(other.col), arr(new int[other.row*other.col])
{
	for (int i = 0; i < other.row; i++)
	{
		for (int j = 0; j < other.col; j++)
		{
			this->arr[i * other.col + j] = other.arr[i * other.col + j];
		}
	}
}

void Matrix::pisi()
{
	for (int i = 0; i < row; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < col; j++)
		{
			std::cout << "  " << this->arr[i * col + j];
		}
	}
}

Matrix::~Matrix()
{
	delete[] this->arr;
}
