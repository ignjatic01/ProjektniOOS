#pragma once
#include <iostream>

class Matrix
{
private:
	int* arr;
	int row;
	int col;
	friend class Fifo;
public:
	Matrix();
	Matrix(int* arr, int row, int col);
	Matrix(int row, int col);
	Matrix(const Matrix& other);
	
	void pisi();
	~Matrix();
};