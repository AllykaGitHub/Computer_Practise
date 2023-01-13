#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
protected:

	int rows;
	int cols;
	std::vector<std::vector<double>> data;

private:

	void Display()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				std::cout << data[i][j] << " ";
			}

			std::cout << std::endl;
		}
	}

	void Set_Elems()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i][j] = rand() % 5;
			}
		}
	}

public:

	// Custom constructor
	Matrix(int m, int n);

	// Copy constructor
	Matrix(const Matrix& matrix);

	// Destructor
	~Matrix();

	friend std::ostream& operator <<(std::ostream& ostr, Matrix& matrix);
		
	friend std::istream& operator >>(std::istream& in, Matrix& matrix);

	Matrix operator +(const Matrix& rhs);

	Matrix operator -(const Matrix& rhs);

	Matrix operator *(const Matrix& rhs);

	Matrix operator *(const double multiplier);

	// Transposed matrix
	Matrix transpose();

};

#endif MATRIX_H