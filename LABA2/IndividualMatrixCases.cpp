#include "IndividualMatrixCases.h"
#include <cassert>

using namespace std;

// DiagonalMatrix

DiagonalMatrix::DiagonalMatrix(int dimension) : Matrix(dimension, dimension) { }

std::istream& operator >>(istream& in, DiagonalMatrix& matrix)
{
	matrix.Set_Elems();
	return (in);
}

// IdentityMatrix

IdentityMatrix::IdentityMatrix(int dimension) : DiagonalMatrix(dimension) { }

std::istream& operator >>(istream& in, IdentityMatrix& matrix)
{
	matrix.Set_Elems();
	return (in);
}

// TriangularMatrix

TriangularMatrix::TriangularMatrix(int dimension, bool isUpper) : Matrix(dimension, dimension)
{
	this->isUpper = isUpper;
}

std::istream& operator >>(istream& in, TriangularMatrix& matrix)
{
	matrix.Set_Elems();
	return (in);
}

// SymmetricMatrix

SymmetricMatrix::SymmetricMatrix(int dimension) : Matrix(dimension, dimension) { }

SymmetricMatrix::SymmetricMatrix(const Matrix& matrix) : Matrix(matrix) { }

std::istream& operator >>(istream& in, SymmetricMatrix& matrix)
{
	matrix.Set_Elems();
	return (in);
}