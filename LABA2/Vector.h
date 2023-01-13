#ifndef VECTOR_H
#define VECTOR_H

#include "Matrix.h"

class ColumnVector : public Matrix
{
public: ColumnVector(int rows);
};

class RowVector : public Matrix
{
public: RowVector(int cols);
};

#endif VECTOR_H