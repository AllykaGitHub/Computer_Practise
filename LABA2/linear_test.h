#include "linear.h"
#include "operator.h"
#include "test_runner.h"

#include <sstream>
#include <cstring>

void TestLinearLibrary() {
    // DEFAULT MATRIX CREATION
    {
        ostringstream ss1, ss2, ss3, ss4, ss5, ss6, ss7, ss8, ss9;
        Linear::Matrix<int> m_int({{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}});
        ss1 << m_int;
        Assert(ss1.str() == "1,      2,      3\n4,      5,      6\n7,      8,      9", "Creation test (1) -> int");
//        Assert(ss1.str() == "[[1, 2, 3],\n[4, 5, 6],\n[7, 8, 9]]", "Creation test (1) -> int");

        Linear::Matrix<float> m_float({{5.3, 6.1},
                                       {0.2, -0.1},
                                       {5.1, 2.9}});
        ss2 << m_float;
        Assert(ss2.str() == "5.3,    6.1\n0.2,   -0.1\n5.1,    2.9", "Creation test (2) -> float");
//        Assert(ss2.str() == "[[5.3, 6.1],\n[0.2, -0.1],\n[5.1, 2.9]]", "Creation test (2) -> float");

        std::vector<std::vector<float>> a;
        Linear::Matrix<float> m_float_2(a);
        ss3 << m_float_2;
        Assert(ss3.str().empty(), "Creation test (3) -> empty float matrix");
//        Assert(ss3.str() == "[[]]", "Creation test (3) -> empty float matrix");

        Linear::Matrix<int> m_int_2({1, 2, 3, 4, 5, 6});
        ss4 << m_int_2;
        Assert(ss4.str() == "1,      2,      3,      4,      5,      6", "Creation test (4) -> one row initialization");
//        Assert(ss4.str() == "[[1, 2, 3, 4, 5, 6]]", "Creation test (4) -> one row initialization");

        Linear::Matrix<int> m_int_3(3, 3);
        ss5 << m_int_3;
        Assert(ss5.str() == "0,      0,      0\n0,      0,      0\n0,      0,      0",
               "Creation test (5) -> initialization by 2 ints");

//        Assert(ss5.str() == "[[0, 0, 0],\n[0, 0, 0],\n[0, 0, 0]]",
//               "Creation test (5) -> initialization by 2 ints");

        Linear::Matrix<int> m_int_4(0, 0);
        ss6 << m_int_4;
        Assert(ss6.str().empty(), "Creation test (6) -> initialization empty matrix by 2 ints");
//        Assert(ss6.str() == "[[]]", "Creation test (6) -> initialization empty matrix by 2 ints");

        Linear::Matrix<int> m_int_5(2);
        ss7 << m_int_5;
        Assert(ss7.str() == "0,      0\n0,      0", "Creation test (7) -> initialization matrix by 1 int");
//        Assert(ss7.str() == "[[0, 0],\n[0, 0]]", "Creation test (7) -> initialization matrix by 1 int");

        Linear::Matrix<int> m_int_6(0);
        ss8 << m_int_6;
        Assert(ss8.str().empty(), "Creation test (8) -> initialization empty matrix by 1 int");
//        Assert(ss8.str() == "[[]]", "Creation test (8) -> initialization empty matrix by 1 int");

        Linear::Matrix<int> m_int_7;
        ss9 << m_int_7;
        Assert(ss9.str() == "0", "Creation test (9) -> default initialization matrix with no arguments");
//        Assert(ss9.str() == "[[0]]", "Creation test (9) -> default initialization matrix with no arguments");

        try {
            Linear::Matrix<int> m_int_8({{1, 2, 3},
                                         {1, 2}});
            Assert(false, "Creation test (10) -> wrong initialization vector given");
        } catch (Linear::IncorrectInitialVector &e) {
            Assert(std::strcmp(e.what(), "Incorrect initial vector, row sizes differ from each other") == 0,
                   "Creation test (10) -> wrong initialization vector given");
        }
    }

    // DEFAULT MATRIX - SIZE
    {
        Linear::Matrix<int> m_int({{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}});
        Assert(m_int.Size() == std::pair<size_t, size_t>{3, 3}, "Size test (1) -> basic");

        Linear::Matrix<int> m_int_2;
        Assert(m_int_2.Size() == std::pair<size_t, size_t>(1, 1), "Size test (2) -> 1 element matrix");

        Linear::Matrix<int> m_int_3(10, 100);
        Assert(m_int_3.Size() == std::pair<size_t, size_t>(10, 100), "Size test (3) -> size by 2 ints");

        try {
            Linear::Matrix<int> m_int_4(-90, -80);
            Assert(false, "Size test (4) -> trying to create matrix with negative size");
        } catch (std::length_error &e) {
            Assert(true, "Size test (4) -> trying to create matrix with negative size");
        }
    }

    // DEFAULT MATRIX - ACCESS TO ELEMENTS
    {
        Linear::Matrix<int> m_int({{1, 2, 3},
                                   {4, 5, 6}});
        Assert(m_int.At(1, 2) == 6, "Access to elements (1) -> At method");
        Assert(m_int.Sel(0, 1) == 2, "Access to elements (2) -> Sel method");

        m_int.At(1, 2) = 10;

        Assert(m_int.Sel(1, 2) == 10, "Access to elements (3) -> At change");

        try {
            m_int.At(10, 10);
            Assert(false, "Access to elements (5) -> trying to access elements that is out of range, At");
        } catch (Linear::OutOfRange &e) {
            Assert(std::strcmp(e.what(), "Row value 10 is out of range.") == 0,
                   "Access to elements (5) -> trying to access elements that is out of range, At");
        }

        try {
            m_int.Sel(10, 10);
            Assert(false, "Access to elements (5) -> trying to access elements that is out of range, Sel");
        } catch (Linear::OutOfRange &e) {
            Assert(std::strcmp(e.what(), "Row value 10 is out of range.") == 0,
                   "Access to elements (5) -> trying to access elements that is out of range, Sel");
        }
    }

    // DEFAULT MATRIX - TRANSPOSE
    {
        Linear::Matrix<int> m_int({{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}});
        Linear::Matrix<int> m_int_2({{1, 4, 7},
                                     {2, 5, 8},
                                     {3, 6, 9}});

        Assert(m_int.Transpose() == m_int_2, "Transposing (1) -> simple transpose");

        Linear::Matrix<int> m_int_3({{1, 2},
                                     {3, 4},
                                     {5, 6}});
        Linear::Matrix<int> m_int_4({{1, 3, 5},
                                     {2, 4, 6}});

        Assert(m_int_3.Transpose() == m_int_4, "Transposing (2) -> Non square matrix");
        auto[rows, cols] = m_int_3.Transpose().Size();
        auto[rows2, cols2] = m_int_4.Size();
        Assert((rows == rows2) && (cols == cols2), "Transposing (3) -> Sizes");

        Linear::Matrix<int> m_int_5(std::vector<std::vector<int>>(1, {0}));
        Assert(m_int_5.Transpose() == m_int_5, "Transposing (4) -> 1 element matrix");
    }

    // DEFAULT MATRIX - SWAP ROWS
    {
        Linear::Matrix<int> m_int({{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}});
        Linear::Matrix<int> m_int_2({{7, 8, 9},
                                     {4, 5, 6},
                                     {1, 2, 3}});
        m_int.swapRows(0, 2);
        Assert(m_int == m_int_2, "Swap rows (1) -> simple swap rows");

        Linear::Matrix<int> m_int_3({{1, 2},
                                     {3, 4},
                                     {5, 6}});
        Linear::Matrix<int> m_int_4({{1, 2},
                                     {5, 6},
                                     {3, 4}});
        m_int_3.swapRows(1, 2);
        Assert(m_int_3 == m_int_4, "Swap rows (2) -> Non square matrix");
    }

    // DEFAULT MATRIX - Determinant (minors)
    {
        Linear::Matrix<int> m_int({{1, 2, 3},
                                   {4, 5, 6},
                                   {7, 8, 9}});
        Assert(m_int.Determinant() == 0, "Determinant (1) -> 0 Determinant");

        Linear::Matrix<int> m_int_2({{90,  87,   56},
                                     {13,  2,    12},
                                     {-91, -871, 32}});
        Assert(m_int_2.Determinant() == 191348, "Determinant (2) -> big Determinant");

        Linear::Matrix<int> m_int_3({{1},
                                     {3},
                                     {5}});
        try {
            m_int_3.Determinant();
            Assert(false, "Determinant (3) -> Not square matrix");
        } catch (Linear::IncompatibleSize &e) {
            Assert(strcmp(e.what(), "Matrix is not a quadratic. Determinant cannot be found!") == 0,
                   "Determinant (3) -> Not square matrix");
        }
    }

    // DEFAULT MATRIX - EXPLICIT VECTOR
    {
        Linear::Matrix<int> m_int({{-9, 8, 13},
                                   {25, 8, 98},
                                   {0,  2, 1}});

        Assert(m_int.getExplicit() == std::vector<std::vector<int>>{{-9, 8, 13},
                                                                    {25, 8, 98},
                                                                    {0,  2, 1}},
               "getExplicit (1) -> default matrix");
    }

    // ANY MATRIX - OPERATOR+, OPERATOR-, OPERATOR*, dot
    {
        Linear::Matrix<int> m_int({{-9, 8, 13},
                                   {25, 8, 98},
                                   {0,  2, 1}});
        Linear::Diagonal<float> m_int_2({1, -28, 39});

        Assert(m_int + m_int_2 == Linear::Matrix<int>({{-8, 8,   13},
                                                       {25, -20, 98},
                                                       {0,  2,   40}}),
               "OPERATOR+ (1) -> usual + diagonal");

        Linear::Unit<float> m_int_3(3);
        Assert(m_int - m_int_3 == Linear::Matrix<int>({{-10, 8, 13},
                                                       {25,  7, 98},
                                                       {0,   2, 0}}),
               "OPERATOR- (2) -> usual - unit");

        Linear::SymmetricMatrix<int> m_int_4({{1, 2, 3},
                                              {2, 5, 9},
                                              {3, 9, 18}});

        Assert(4 * m_int_4 == Linear::SymmetricMatrix<int>({{4,  8,  12},
                                                            {8,  20, 36},
                                                            {12, 36, 72}}),
               "OPERATOR* (3) -> number * symmetric");

        Assert(0 * m_int_4 == Linear::Matrix<int>(3), "OPERATOR * (4) -> 0 * symmetric == 0");

        Linear::UpperTriangular<int> m_int_5({{1, 7,  -8},
                                              {0, 19, -2},
                                              {0, 0,  3}});
        Assert(m_int_5.dot(Linear::Unit<int>(3)) == m_int_5, "Dot (5) -> matrix * unit matrix");

        try {
            m_int_5.dot(Linear::Unit<int>(4));
            Assert(false, "Dot (6) -> incompatible matrix sizes during multiplication");
        } catch (Linear::IncompatibleSize &e) {
            Assert(strcmp(e.what(), "Can't multiply matrix when columns of the first one (3) do not equal to rows of "
                                    "the second (4)!") == 0,
                   "Dot (6) -> incompatible matrix sizes during multiplication");
        }

        try {
            m_int_5 + Linear::Diagonal<int>(100);
            Assert(false, "Dot (6) -> incompatible matrix sizes during adding");
        } catch (Linear::IncompatibleSize &e) {
            Assert(strcmp(e.what(), "Cannot add matrixes with different sizes") == 0,
                   "Dot (6) -> incompatible matrix sizes during adding");
        }

        Assert(Linear::Unit<int>(5) * Linear::Diagonal<int>({1, 2, 3, 4, 5}) == Linear::Diagonal<int>({1, 2, 3, 4, 5}),
               "Operator* for 2 matrix (1) -> Diagonal * Unit");

        Assert(Linear::Matrix<float>({{1,   2,    3},
                                      {6.5, 8.0,  13},
                                      {12,  -9.5, 0}}) * Linear::Matrix<float>({{2,   5,  2},
                                                                                {2,   1,  0},
                                                                                {0.5, -2, 5}}) == Linear::Matrix<float>(
                {{2,  10, 6},
                 {13, 8,  0},
                 {6,  19, 0}}), "Operator* for 2 matrix (2) -> matrix * matrix");
    }

    // DEFAULT MATRIX - getUpperTriangularForm
    {
        Assert(round(Linear::Matrix<int>({{1,  2, 3},
                                          {6,  1, 2},
                                          {13, 9, 0}}).getUpperTriangularForm().Determinant()) == 157,
               "getUpperTriangularForm (1) -> determinant test");
        Assert(Linear::Matrix<int>({{1, 2, 3},
                                    {0, 1, 2},
                                    {0, 0, 90}}).getUpperTriangularForm() == Linear::Matrix<double>({{1, 2, 3},
                                                                                                     {0, 1, 2},
                                                                                                     {0, 0, 90}}),
               "getUpperTriangularForm (2) -> already triangular matrix");
    }

    // DEFAULT MATRIX - Track
    {
        Assert(Linear::Matrix<float>({{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9}}).Track() == 15,
               "Track (0) -> default float matrix");

        Assert(Linear::Matrix<float>({{0, 2, 3},
                                      {4, 0, 6},
                                      {7, 8, 0}}).Track() == 0,
               "Track (1) -> zero track float matrix");

        try {
            Linear::Matrix<int>({1, 2, 3}).Track();
            Assert(false, "Track (2) -> Track for not square matrix error");
        } catch (Linear::IncompatibleSize &e) {
            Assert(strcmp(e.what(), "Track for not square matrix is not defined") == 0,
                   "Track (2) -> Track for not square matrix error");
        }
    }

    // DEFAULT MATRIX - Sum
    {
        Assert(Linear::Matrix<float>({{6,  2,  8.5},
                                      {13, 21, -9.5}}).Sum() == 41,
               "Default matrix sum (1) -> simple sum");

        Assert(Linear::Matrix<int>({{1,  2,  3},
                                    {-3, -2, -1}}).Sum() == 0,
               "Default matrix sum (2) -> zero sum");
    }

    // DEFAULT MATRIX - Norm
    {
        Assert(Linear::Matrix<float>({1, 2, 3, 1, 1}).Norm() == 4, "Matrix norm (1) -> vector norm");
        Assert(Linear::Matrix<int>({0, 0, 0, 0}).Norm() == 0, "Matrix norm (2) -> zero vector");
        Assert(Linear::Matrix<int>({{1, 0, 3},
                                    {4, 5, 6},
                                    {7, 8, 5}}).Norm() == 15,
               "Matrix norm (3) -> matrix norm");

        Assert(Linear::Matrix<float>({{1,   2,  3},
                                      {-5,  -8, 19},
                                      {-98, 0,  1}}).Norm(Linear::NormType::Max) == 98,
               "Matrix norm (4) -> Max norm of matrix");

        Assert(Linear::Matrix<int>({1, 2, 3, 4, -8, 13}).Norm(Linear::NormType::Max) == 13,
               "Matrix norm (5) -> Max norm of vector");

        std::vector<std::vector<int>> vec;
        Assert(Linear::Matrix<int>(vec).Norm(Linear::NormType::Max) == 0,
               "Matrix norm (6) -> Empty vector norm");

    }

    // DEFAULT MATRIX - Reverse
    {
        Linear::Matrix<double> m_int({{1, 2, 3}, {4, 5, 6}, {7, 8, 10}});
        Assert(Linear::Unit<double>(3) == m_int.dot(m_int.Reverse()),
                "Reverse matrix (1) -> Default matrix");

        Linear::Matrix<int> m_int_2({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        try {
            m_int_2.Reverse();
            Assert(false,"Reverse matrix (2) -> Matrix with zero determinant");
        } catch (Linear::ZeroDeterminant& e) {
            Assert(strcmp(e.what(), "Determinant equals to zero. Matrix cannot be reversed") == 0,
                   "Reverse matrix (2) -> Matrix with zero determinant");
        }
    }

    // MATRIX RANK
    {
        Linear::Matrix<int> m_int({{-2, 3,   1,  0,  -4},
                                   {0,  0,   0,  5,  -6},
                                   {4,  -11, -5, 12, 18},
                                   {-9, 6,   0,  -2, 21},
                                   {-5, 5,   1,  1,  1}});

        Assert(m_int.Rank() == 3, "Matrix rank (1) -> Big matrix");
        Assert(Linear::Matrix<int>({1, 2, 3, 4, 5}).Rank() == 1, "Matrix rank (2) -> Vector rank");
        Assert(Linear::Matrix<int>(1, 2).Rank() == 0, "Matrix rank (3) -> zero matrix rank");
        Assert(Linear::Unit<int>(5).Rank() == 5, "Matrix rank (4) -> Unit matrix rank");
    }
}

void TestVectors() {
    // VECTOR MULTIPLICATION
    {
        Linear::Matrix<int> vec({1, 2, 3, 4, 5});
        Linear::Matrix<int> vec2 = Linear::Matrix<int>({-1, -2, -3, -4, -5});

        Assert(vec.dot(vec2.Transpose()).At(0, 0) == -55,
               "Vector multiplication (1) -> Scalar vector multiplication");

        Assert(vec * vec2 == Linear::Matrix<int>({-1, -4, -9, -16, -25}),
               "Vector multiplication (2) -> Adamar vector multiplication");
    }

    // ANGLE BETWEEN VECTORS - OPERATOR^
    {
        Linear::Matrix<int> v1({3, 4, 0});
        Linear::Matrix<int> v2({4, 4, 2});

        Assert((v1 ^ v2) == acos((3 * 4 + 4 * 4) / (pow(25, 0.5) * pow(36, 0.5))),
               "Angle between vectors (1) -> simple vectors");

        Linear::Matrix<int> v3({3, 4, -5});
        Linear::Matrix<int> v4({3, 4, 5});
        Assert((v3 ^ v4) == 1, "Angle between vectors (2) -> zero scalar");

        Linear::Matrix<int> v5({0, 0, 0});
        Assert((v3 ^ v5) == 1, "Angle between vectors (3) -> vector with zero norm");

        try {
            Linear::Matrix<float>({{1, 2, 3},
                                   {8, 9, 0}}) ^ Linear::Matrix<float>({9, 8, 2});
            Assert(false, "Angle between vectors (4) -> Trying to calculate angle between matrix and vector");
        } catch (Linear::IncompatibleSize &e) {
            Assert(strcmp(e.what(), "Cannot calculate the angle of not vector objects") == 0,
                   "Angle between vectors (4) -> Trying to calculate angle between matrix and vector");
        }

        try {
            Linear::Matrix<int>({1, 2, 3, 4, 5}) ^ Linear::Matrix<int>({2, 3, 4});
            Assert(false, "Angle between vectors (5) -> Trying to calculate angle between vectors of different sizes");
        } catch (Linear::IncompatibleSize &e) {
            Assert(strcmp(e.what(), "Sizes are incompatible, cannot do the componentwise multiplication") == 0,
                   "Angle between vectors (5) -> Trying to calculate angle between vectors of different sizes");
        }
    }
}

void TestDiagonalMatrix() {
    // DIAGONAL - CREATION
    {
        Assert(Linear::Diagonal<int>({1, 2, 3}) == Linear::Diagonal<int>({{1, 0, 0},
                                                                          {0, 2, 0},
                                                                          {0, 0, 3}}),
               "Diagonal matrix creation (1) -> 2 ways are equal");

        Assert(Linear::Diagonal<int>({5, 6, 8}) == Linear::Matrix<int>({{5, 0, 0},
                                                                        {0, 6, 0},
                                                                        {0, 0, 8}}),
               "Diagonal matrix creation (2) -> one of previous two in correct");
        try {
            Linear::Diagonal<int>({{1, 2},
                                   {4, 5}});
            Assert(false, "Diagonal matrix creation (3) -> error when incorrect");
        } catch (Linear::WrongFormat &e) {
            Assert(strcmp(e.what(), "Diagonal matrix elements which does not belong to the diagonal must be zeros"),
                   "Diagonal matrix creation (3) -> error when incorrect");
        }
    }

    // DIAGONAL - At on the not diagonal element
    {
        try {
            Linear::Diagonal<int>({1, 2, 3}).At(2, 3) = 0;
            Assert(false, "Diagonal at (1) -> non diagonal element");
        } catch (Linear::OutOfRange &e) {
            Assert(strcmp(e.what(), "You can't change not diagonal elements in diagonal matrix") == 0,
                   "Diagonal at (1) -> non diagonal element");
        }

        Linear::Diagonal<int> m_int({7, 8, 9, 1});
        m_int.At(2, 2) = 91;
        Assert(m_int.At(0, 0) == 7, "Diagonal At (2) -> get diagonal element");
        Assert(m_int == Linear::Diagonal<int>({7, 8, 91, 1}), "Diagonal At (3) -> Change diagonal element");

        Assert(m_int.At(3) == 1, "Diagonal At (4) -> single index At");
        m_int.At(3) = 12;
        Assert(m_int == Linear::Diagonal<int>({7, 8, 91, 12}),
               "Diagonal At (5) -> Change diagonal element by single index At");

        try {
            m_int.At(100);
            Assert(false, "Diagonal At (6) -> out of range");
        } catch (Linear::OutOfRange &e) {
            Assert(strcmp(e.what(), "Row value 100 is out of range.") == 0, "Diagonal At (6) -> out of range");
        }
    }

    // DIAGONAL - DETERMINANT
    {
        Linear::Diagonal<int> m_int({1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 90, 213213});
        Assert(m_int.Determinant() == 0, "Diagonal determinant (1) -> zero determinant of large matrix");

        Linear::Diagonal<int> m_int_2({1, 2, 3, 4, 5, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1});
        Assert(m_int_2.Determinant() == 720, "Diagonal determinant (2) -> determinant of large matrix");
    }
};

void TestUnitMatrix() {
    // UNIT CONSTRUCTOR
    {
        Assert(Linear::Unit<int>(3) == Linear::Matrix<int>({{1, 0, 0},
                                                            {0, 1, 0},
                                                            {0, 0, 1}}),
               "Unit matrix constructor (1)");
    }

    // UNIT DETERMINANT
    {
        Assert(Linear::Unit<int>(1).Determinant() == 1, "Unit determinant (1)");
        Assert(Linear::Unit<float>(100).Determinant() == 1, "Unit determinant (2)");
        Assert(Linear::Unit<uint8_t>(19).Determinant() == 1, "Unit determinant (3)");
        Assert(Linear::Unit<double>(13).Determinant() == 1, "Unit determinant (4)");
        Assert(Linear::Unit<int8_t>(19).Determinant() == 1, "Unit determinant (5)");
        Assert(Linear::Unit<char>(1).Determinant() == 1, "Unit determinant (6)");
    }
}

void TestUpperTriangularMatrix() {
    // UPPER TRIANGULAR CREATION
    {
        Linear::UpperTriangular<int> m_int({{1, 2, 3},
                                            {0, 2, 3},
                                            {0, 0, 4}});
        Assert(m_int == Linear::Matrix<int>({{1, 2, 3},
                                             {0, 2, 3},
                                             {0, 0, 4}}),
               "Upper triangular creation (1) -> simple creation test");

        try {
            Linear::UpperTriangular<int> m_int_2({{1, 2, 3},
                                                  {0, 2, 3},
                                                  {1, 0, 4}});
            Assert(false, "Upper triangular creation (2) -> wrong initial format");
        } catch (Linear::OutOfRange &e) {
            Assert(strcmp(e.what(), "Upper triangular matrix cannot have non zero elements below the diagonal") == 0,
                   "Upper triangular creation (2) -> wrong initial format");
        }
    }

    // UPPER TRIANGULAR AT
    {
        try {
            Linear::UpperTriangular<int>({{1, 2, 3},
                                          {0, 2, 5}}).At(1, 0);
            Assert(false, "Upper triangular At (1) -> cannot access to the element below the diagonal");
        } catch (Linear::OutOfRange &e) {
            Assert(strcmp(e.what(), "Cannot access the elements below the diagonal in the upper triangular matrix") ==
                   0,
                   "Upper triangular At (1) -> cannot access to the element below the diagonal");
        }

        Linear::UpperTriangular<int> m_int({{1, -6, 18},
                                            {0, 13, 2}});
        Assert(m_int.At(1, 1) == 13, "Upper triangular At (2) -> access to the element above the diagonal");
    }

    // UPPER TRIANGULAR DETERMINANT
    {
        Linear::UpperTriangular<int> m_int({{1, 2, 3},
                                            {0, 5, 6},
                                            {0, 0, 9}});
        Assert(m_int.Determinant() == 45, "Upper triangular determinant (1) -> simple determinant");

        Linear::UpperTriangular<int> m_int_2({{1, 2, 3},
                                              {0, 5, 6}});
        try {
            m_int_2.Determinant();
            Assert(false, "Upper triangular determinant (2) -> not square matrix determinant");
        } catch (Linear::WrongFormat &e) {
            Assert(strcmp(e.what(), "Determinant can only be calculated for square matrix.") == 0,
                   "Upper triangular determinant (2) -> not square matrix determinant");
        }
    }
}

void TestLowerTriangular() {
    // LOWER TRIANGULAR CREATION
    {
        Linear::LowerTriangular<int> m_int({{1,  0, 0},
                                            {5,  6, 0},
                                            {13, 9, 81}});
        Assert(m_int == Linear::Matrix<int>({{1,  0, 0},
                                             {5,  6, 0},
                                             {13, 9, 81}}),
               "Lower triangular creation (1) -> simple creation test");

        try {
            Linear::LowerTriangular<int>({{1, 2, 3},
                                          {8, 9, 10}});
            Assert(false, "Lower triangular creation (2) -> wrong initial matrix test");
        } catch (Linear::OutOfRange &e) {
            Assert(strcmp(e.what(), "Lower triangular matrix cannot have non zero elements above the diagonal") == 0,
                   "Lower triangular creation (2) -> wrong initial matrix test");
        }
    }

    // LOWER TRIANGULAR AT
    {
        try {
            Linear::LowerTriangular<int>({{1, 0, 0},
                                          {1, 2, 0}}).At(0, 1);
            Assert(false, "Lower triangular At (1) -> cannot access to the element above the diagonal");
        } catch (Linear::OutOfRange &e) {
            Assert(strcmp(e.what(), "Cannot access the elements above the diagonal in the lower triangular matrix") ==
                   0,
                   "Lower triangular At (1) -> cannot access to the element above the diagonal");
        }

        Linear::LowerTriangular<int> m_int({{1, 0, 0},
                                            {0, 13, 0}});
        Assert(m_int.At(1, 0) == 0, "Lower triangular At (2) -> access to the element below the diagonal");
    }
}

void TestSymmetricMatrix() {
    // SYMMETRIC MATRIX CREATION
    {
        Linear::SymmetricMatrix<int> m_int({{1, 2, 3},
                                            {2, 5, 8},
                                            {3, 8, 90}});

        Assert(m_int == Linear::Matrix<int>({{1, 2, 3},
                                             {2, 5, 8},
                                             {3, 8, 90}}),
               "Symmetric matrix creation (1) -> simple creation");

        try {
            Linear::SymmetricMatrix<int>({{1, 2, 3},
                                          {2, 5, 9},
                                          {3, 8, 91}});
            Assert(false, "Symmetric matrix creation (2) -> non symmetric initial matrix error");
        } catch (Linear::WrongFormat &e) {
            Assert(strcmp(e.what(), "Initial matrix is not symmetric") == 0,
                   "Symmetric matrix creation (2) -> non symmetric initial matrix error");
        }
    }
}
