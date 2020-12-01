#pragma once
#include <iostream>
#include <ctime>

class Matrix
{
	int** m_matrix;
	int m_number_of_columns;
	int m_number_of_rows;
	int m_minimal_row;
	int m_minimal_column;

	int* m_set;
	int m_size_of_set;
public:
	Matrix();
	Matrix(const Matrix&);
	~Matrix();
	void setSize();
	void setRows(int);
	void setColumns(int);
	void fillMatrixRandom();
	void fillMatrixManually();
	void showMatrix();
	void findMinimal();
	void zeroing();
	void zeroRow();
	void zeroColumn();
	void swapFirstAndUneven();
	friend void operator+(Matrix, Matrix);
	void createSet(Matrix&);
};