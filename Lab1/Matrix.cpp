#include "Matrix.h"
#include "Tools.h"
using namespace std;

Matrix::Matrix()
{
	setSize();
	m_matrix = new int* [m_number_of_rows];
	for (int i = 0; i < m_number_of_rows; i++)
		m_matrix[i] = new int[m_number_of_columns];
	//cout << "Matrix[" << m_number_of_rows << ";" << m_number_of_columns << "] was created!" << endl;
	//cout << endl;
}

Matrix::Matrix(const Matrix& other)
{
	//cout << "Copy constructor is working" << endl;
	m_number_of_rows = other.m_number_of_rows;
	m_number_of_columns = other.m_number_of_columns;
	m_minimal_row = other.m_minimal_row;
	m_minimal_column = other.m_number_of_columns;

	m_matrix = new int* [other.m_number_of_rows];
	for (int i = 0; i < other.m_number_of_rows; i++)
	{
		m_matrix[i] = new int[other.m_number_of_columns];
	}

	for (int i = 0; i < other.m_number_of_rows; i++)
		for (int j = 0; j < other.m_number_of_columns; j++)
			m_matrix[i][j] = other.m_matrix[i][j];

	m_size_of_set = other.m_size_of_set;
	for (int i = 0; i < other.m_size_of_set; i++)
	{
		m_set[i] = other.m_set[i];
	}
}

void Matrix::setSize()
{
	cout << "Nuber of rows: ";
	int number_of_rows = inputNaturalNumber();
	setRows(number_of_rows);

	cout << "Number of columns: ";
	int number_of_columns = inputNaturalNumber();
	setColumns(number_of_columns);
}

void Matrix::setRows(int number_of_rows = SIZE_OF_MATRIX)
{
	m_number_of_rows = number_of_rows;
}

void Matrix::setColumns(int number_of_columns = SIZE_OF_MATRIX)
{
	m_number_of_columns = number_of_columns;
}

Matrix::~Matrix()
{
	for (int i = 0; i < m_number_of_rows; i++)
		delete[]m_matrix[i];
	delete[]m_matrix;
	delete[]m_set;
	//cout << "Matrix[" << m_number_of_rows << ";" << m_number_of_columns << "] was deleted" << endl;
}

void Matrix::fillMatrixRandom()
{
	srand(time(NULL));
	for (int i = 0; i < m_number_of_rows; i++)
		for (int j = 0; j < m_number_of_columns; j++)
		{
			m_matrix[i][j] = rand() % RAND_INTERVAL + 1;
		}
}

void Matrix::fillMatrixManually()
{
	for (int i=0; i<m_number_of_rows; i++)
		for (int j = 0; j < m_number_of_columns; j++)
		{
			cout << "element[" << i + 1 << ";" << j + 1 << "] = ";
			m_matrix[i][j] = inputNaturalNumber();
		}
}

void Matrix::showMatrix()
{
	for (int i = 0; i < m_number_of_rows; i++)
	{
		for (int j = 0; j < m_number_of_columns; j++)
			cout << m_matrix[i][j] << " \t";
		cout << endl;
	}
	cout << endl;
}

void Matrix::findMinimal()
{
	m_minimal_row = 0;
	m_minimal_column = 0;
	for (int i = 0; i < m_number_of_rows; i++)
		for (int j = 0; j < m_number_of_columns; j++)
			if (m_matrix[i][j] < m_matrix[m_minimal_row][m_minimal_column])
			{
				m_minimal_row = i;
				m_minimal_column = j;
			}
}

void Matrix::zeroing()
{
	findMinimal();
	cout << "Minimal element: " << m_matrix[m_minimal_row][m_minimal_column] << " at " << m_minimal_row + 1 << " row " <<
		m_minimal_column + 1 << " column" << endl;
	zeroRow();
	zeroColumn();
}

void Matrix::zeroRow()
{
	for (int i = 0; i < m_number_of_rows; i++)
	{
		m_matrix[i][m_minimal_column] = 0;
	}
}

void Matrix::zeroColumn()
{
	for (int i = 0; i < m_number_of_columns; i++)
	{
		m_matrix[m_minimal_row][i] = 0;
	}
}

void Matrix::swapFirstAndUneven()
{
	cout << "First uneven in the row swap with the first element in that row" << endl;
	for (int i = 0; i < m_number_of_rows; i++)
		for (int j = 0; j < m_number_of_columns; j++)
		{
			if (m_matrix[i][j] % 2 != 0)
			{
				swap(m_matrix[i][0], m_matrix[i][j]);
				break;
			}
		}
}

void operator+(Matrix first_matrix, Matrix second_matrix)
{
	first_matrix.createSet(first_matrix);
	second_matrix.createSet(second_matrix);

	int size_of_result_set = first_matrix.m_size_of_set;
	for (int i = 0; i < second_matrix.m_size_of_set; i++)
	{
		bool is_equal=false;
		for (int j = 0; j < first_matrix.m_size_of_set; j++)
		{
			if (first_matrix.m_set[j] == second_matrix.m_set[i])
			{
				is_equal = true;
				break;
			}
		}
		if (!is_equal)
		{
			size_of_result_set++;
		}
	}

	int* result_set = new int[size_of_result_set];

	int count = 0;
	for (int i = 0; i < first_matrix.m_size_of_set; i++)
	{
		result_set[count++] = first_matrix.m_set[i];
	}

	for (int i = 0; i < second_matrix.m_size_of_set; i++)
	{
		bool is_equal = false;
		for (int j = 0; j < first_matrix.m_size_of_set; j++)
		{
			if (first_matrix.m_set[j] == second_matrix.m_set[i])
			{
				is_equal = true;
			}
		}
		if (!is_equal)
		{
			result_set[count++] = second_matrix.m_set[i];
		}
	}

	for (int i = 0; i < size_of_result_set; i++)
	{
		for (int j = 0; j < size_of_result_set - 1; j++)
		{
			if (result_set[i] < result_set[j])
			{
				swap(result_set[i], result_set[j]);
			}
		}
	}

	for (int i = 0; i < size_of_result_set; i++)
	{
		cout << result_set[i] << " ";
	}
	cout << endl;
	delete[]result_set;
}

void Matrix::createSet(Matrix& matrix)
{
	matrix.m_size_of_set = matrix.m_number_of_rows * matrix.m_number_of_columns;

	int* set_temp = new int[matrix.m_size_of_set];
	for (int i = 0, k = 0; i < matrix.m_number_of_rows; i++)
	{
		for (int j = 0; j < matrix.m_number_of_columns; j++)
		{
			set_temp[k++] = matrix.m_matrix[i][j];
		}
	}

	for (int i = 0; i < matrix.m_size_of_set; i++)
	{
		for (int j = i + 1; j < matrix.m_size_of_set; j++)
		{
			if (set_temp[i] == set_temp[j])
			{
				for (int k = j; k < matrix.m_size_of_set - 1; k++)
				{
					set_temp[k] = set_temp[k + 1];
				}
				matrix.m_size_of_set--;
				j--;
			}
		}
	}

	matrix.m_set = new int[matrix.m_size_of_set];
	for (int i = 0; i < matrix.m_size_of_set; i++)
	{
		matrix.m_set[i] = set_temp[i];
	}
	delete[]set_temp;
}