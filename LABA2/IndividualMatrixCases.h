#ifndef INDIVIDUAL_MATRIX_CASES
#define INDIVIDUAL_MATRIX_CASES

#include "Matrix.h"

// DiagonalMatrix

class DiagonalMatrix : public Matrix
{
private:
	void Set_Elems()
	{
		for (int i = 0; i < rows; i++) { data[i][i] = rand() % 5; }
	}

public:
	DiagonalMatrix(int dimension);

	friend std::istream& operator >>(std::istream& in, DiagonalMatrix& matrix);
};

// IdentityMatrix

class IdentityMatrix : public DiagonalMatrix
{
private:
	void Set_Elems()
	{
		for (int i = 0; i < rows; i++) { data[i][i] = 1; }
	}

public:
	IdentityMatrix(int dimension);

	friend std::istream& operator >>(std::istream& in, IdentityMatrix& matrix);
};

// TriangularMatrix

class TriangularMatrix : public Matrix
{
protected:
	bool isUpper;

private:
	void Set_Elems()
	{
		if (isUpper) {
			for (int i = 0; i < rows; i++)
			{
				for (int j = i; j < cols; j++) { data[i][j] = rand() % 5; }
			}
		}
		else {
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < i + 1; j++) { data[i][j] = rand() % 5; }
			}
		}
	}

public:
	TriangularMatrix(int dimension, bool isUpper);

	friend std::istream& operator >>(std::istream& in, TriangularMatrix& matrix);
};

// SymmetricMatrix

class SymmetricMatrix : public Matrix
{
private:
	void Set_Elems()
	{
		// Создадим верхнетреугольную матрицу, чтобы в дальнейшем транспонировать ее
		// и получить "зеркальную" нижнетреугольную часть
		auto triangularMatrix = TriangularMatrix(rows, true);
		std::cin >> triangularMatrix;

		// Так как симметричная матрица равна своей транспонированной, мы можем создать ее нижнюю от главной диагонали часть
		// с помощью транспонирования верхнетреугольной матрицы (или наоборот)
		auto transposedMatrix = triangularMatrix.transpose();

		// В результате, сложив две части, получаем матирцу, которая гарантированно равна своей транспонированной,
		// т. е. симметричную относительно главной диагонали
		auto resultMatrix = triangularMatrix + transposedMatrix;

		*this = resultMatrix;
	}

public:
	SymmetricMatrix(int dimension);

	SymmetricMatrix(const Matrix& matrix);

	friend std::istream& operator >>(std::istream& in, SymmetricMatrix& matrix);
};

#endif INDIVIDUAL_MATRIX_CASES