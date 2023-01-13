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
		// �������� ����������������� �������, ����� � ���������� ��������������� ��
		// � �������� "����������" ���������������� �����
		auto triangularMatrix = TriangularMatrix(rows, true);
		std::cin >> triangularMatrix;

		// ��� ��� ������������ ������� ����� ����� �����������������, �� ����� ������� �� ������ �� ������� ��������� �����
		// � ������� ���������������� ����������������� ������� (��� ��������)
		auto transposedMatrix = triangularMatrix.transpose();

		// � ����������, ������ ��� �����, �������� �������, ������� �������������� ����� ����� �����������������,
		// �. �. ������������ ������������ ������� ���������
		auto resultMatrix = triangularMatrix + transposedMatrix;

		*this = resultMatrix;
	}

public:
	SymmetricMatrix(int dimension);

	SymmetricMatrix(const Matrix& matrix);

	friend std::istream& operator >>(std::istream& in, SymmetricMatrix& matrix);
};

#endif INDIVIDUAL_MATRIX_CASES