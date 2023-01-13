#include "Vector.h"

using namespace std;

ColumnVector::ColumnVector(int rows) : Matrix(rows, 1) { }

RowVector::RowVector(int cols) : Matrix(1, cols) { }