#include <time.h>

#include "Vector.h"
#include "IndividualMatrixCases.h"

using namespace std;

int main()
{
	srand(time(NULL));

	cout << "ColumnVector:" << endl;
	auto columnVector = ColumnVector(4);
	cin >> columnVector;
	cout << columnVector << endl;

	cout << "RowVector:" << endl;
	auto rowVector = RowVector(4);
	cin >> rowVector;
	cout << rowVector << endl;

	cout << "Multiplication of ColumnVector & RowVector:" << endl;
	auto vectorMul = columnVector * rowVector;
	cout << vectorMul << endl;

	cout << "Matrix A:" << endl;
	auto matrix1 = Matrix(3, 2);
	cin >> matrix1;
	cout << matrix1 << endl;

	cout << "Matrix B:" << endl;
	auto matrix2 = Matrix(2, 3);
	cin >> matrix2;
	cout << matrix2 << endl;

	cout << "Multiplication of Matrix A & Matrix B:" << endl;
	auto matrixMul = matrix1 * matrix2;
	cout << matrixMul << endl;

	cout << "Symmetric Matrix:" << endl;
	auto symmetricMatrix = SymmetricMatrix(5);
	cin >> symmetricMatrix;
	cout << symmetricMatrix << endl;

	system("pause");
}