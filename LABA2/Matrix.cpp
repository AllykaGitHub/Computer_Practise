#include "Matrix.h"
#include <cassert>

using namespace std;

Matrix::Matrix(int rows, int cols)
{
	assert(rows > 0 && cols > 0);

	this->rows = rows;
	this->cols = cols;

	data = vector<vector<double>>(rows);
	for (int i = 0; i < rows; i++)
	{
		data[i] = vector<double>(cols);
	}
}

Matrix::Matrix(const Matrix& matrix)
{
	rows = matrix.rows;
	cols = matrix.cols;
	data = matrix.data;
}

Matrix::~Matrix() { }

std::ostream& operator <<(ostream& ostr, Matrix& matrix)
{
	matrix.Display();
	return (ostr);
}

std::istream& operator >>(istream& in, Matrix& matrix)
{
	matrix.Set_Elems();
	return (in);
}

Matrix Matrix::operator +(const Matrix& rhs)
{
	assert(rows == rhs.rows && cols == rhs.cols && "Размеры матриц не совпадают.");

	auto new_matrix = Matrix(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] + rhs.data[i][j];
		}
	}
	return new_matrix;
}

Matrix Matrix::operator -(const Matrix& rhs)
{
	assert(rows == rhs.rows && cols == rhs.cols && "Размеры матриц не совпадают.");

	auto new_matrix = Matrix(rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] - rhs.data[i][j];
		}
	}
	return new_matrix;
}

Matrix Matrix::operator *(const Matrix& rhs)
{
	assert(cols == rhs.rows && "Кол-во столбцов левой матрицы не совпадает с кол-вом строк правой.");

	int rows = this->rows;
	int cols = rhs.cols;

	auto new_matrix = Matrix(rows, cols);

	for (unsigned i = 0; i < rows; i++) 
	{
		for (unsigned j = 0; j < cols; j++)
		{
			for (unsigned k = 0; k < rhs.rows; k++)
			{
				new_matrix.data[i][j] += this->data[i][k] * rhs.data[k][j];
			}
		}
	}

	return new_matrix;
}

Matrix Matrix::operator *(const double multiplier)
{
	auto new_matrix = Matrix(rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_matrix.data[i][j] = this->data[i][j] * multiplier;
		}
	}

	return new_matrix;
}

Matrix Matrix::transpose()
{
	auto new_matrix = Matrix(cols, rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			new_matrix.data[j][i] = this->data[i][j];
		}
	}

	return new_matrix;
}