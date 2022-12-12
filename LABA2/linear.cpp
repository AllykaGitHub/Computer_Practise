#include <cmath>

#include <iostream>
#include "operator.h"
#include "linear.h"
#include "exception.h"
#include <fstream>

template <typename T>
Linear::Matrix<T>::Matrix(const std::vector<std::vector<T>>& matrix) : _matrix(matrix.begin(), matrix.end()),
                                                                       _rows(matrix.size()),
                                                                       _columns(0) {
    if (_matrix.empty()) return;

    _columns = _matrix[0].size();
    for (const auto& row : _matrix) {
        if (row.size() != _columns) throw Linear::IncorrectInitialVector("Incorrect initial vector, "
                                                                         "row sizes differ from each other");
    }
}

template<typename T>
Linear::Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> _list) : _matrix(_list.begin(), _list.end()),
                                                                                   _rows(_list.size()),
                                                                                   _columns(0) {

    if (_matrix.size() != 0) {
        _columns = _matrix[0].size();
    }

    for (const auto& row : _matrix) {
        if (row.size() != _columns) throw Linear::IncorrectInitialVector("Incorrect initial vector, "
                                                                         "row sizes differ from each other");
    }


}

template <typename T>
Linear::Matrix<T>::Matrix(const std::vector<T>& row) : _matrix(1, std::vector<T>(row.begin(), row.end())), _rows(1), _columns(row.size()) {}

template <typename T>
Linear::Matrix<T>::Matrix(int rows, int cols) : _matrix(rows, std::vector<T>(cols, T(0))), _rows(rows), _columns(cols) {}

template <typename T>
Linear::Matrix<T>::Matrix(int N) : _matrix(N, std::vector<T>(N, T(0))), _rows(N), _columns(N) {}

template <typename T>
Linear::Matrix<T>::Matrix() : _matrix(1, std::vector<T>(1, T(0))), _rows(1), _columns(1) {}

template <typename T>
std::vector<std::vector<T>> Linear::Matrix<T>::getExplicit() const {
    return _matrix;
}


template <typename T>
T& Linear::Matrix<T>::At(size_t i, size_t j) {
    if (i >= _rows) throw OutOfRange("Row value " + std::to_string(i) + " is out of range.");
    if (j >= _columns) throw OutOfRange("Column value " + std::to_string(j) + " is out of range.");
    T& element = _matrix[i][j];
    return element;
}

template <typename T>
T Linear::Matrix<T>::Sel(size_t i, size_t j) const {
    if (i >= _rows) throw OutOfRange("Row value " + std::to_string(i) + " is out of range.");
    if (j >= _columns) throw OutOfRange("Column value " + std::to_string(j) + " is out of range.");
    return _matrix[i][j];
}

template <typename T>
void Linear::Matrix<T>::swapRows(size_t i, size_t j) {
    if (i >= _rows || j >= _rows) throw Linear::OutOfRange("Rows indexes are out of range!");

    std::swap(_matrix[i], _matrix[j]);
}

template <typename T>
Linear::UpperTriangular<double> Linear::Matrix<T>::getUpperTriangularForm() const {
    Linear::Matrix<double> triangular(_rows, _columns);
    for (size_t i  = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            triangular.At(i, j) = static_cast<double>(Sel(i, j));
        }
    }
    int swapsCount = 0, fakeSwaps = 0;
    for (size_t i = 0; i < _columns && swapsCount < _rows; ++i) {
        double max = triangular.Sel(swapsCount, i);
        size_t maxIndex = swapsCount;
        for (size_t row = swapsCount + 1; row < _rows; ++row) {
            if ((triangular.Sel(row, i) != 0) && ((max == 0) || (triangular.Sel(row, i) > max))) {
                max = triangular.Sel(row, i);
                maxIndex = row;
            }
        }

        if (max == 0) continue;

        triangular.swapRows(maxIndex, swapsCount++);
        if (maxIndex == swapsCount - 1) ++fakeSwaps;
        for (size_t j = swapsCount; j < _rows; ++j) {
            double q = triangular.Sel(j, i) / triangular.Sel(swapsCount - 1, i);
            for (size_t k = 0; k < _columns; ++k) {
                triangular.At(j, k) -= triangular.Sel(swapsCount - 1, k) * q;
                if (fabs(triangular.Sel(j, k)) < Linear::epsilon) triangular.At(j, k) = T(0);
            }
        }
    }

    return  Linear::UpperTriangular<double> ((pow(-1, swapsCount - fakeSwaps) * triangular).getExplicit());
}


template <typename T>
T Linear::Matrix<T>::Determinant() const {
    if (_columns != _rows)
        throw Linear::IncompatibleSize("Matrix is not a quadratic. Determinant cannot be found!");
    if (_columns == 0) return T(0);
    if (_columns == 1) return _matrix[0][0];

    T determinant = 0;
    for (size_t i = 0; i < _columns; ++i) {
        Matrix<T> minor(_rows - 1, _columns - 1);
        for (size_t j = 1; j < _rows; ++j) {
            size_t decrease = 0;
            for (size_t k = 0; k < _columns; ++k) {
                if (k == i) {
                    decrease = 1;
                    continue;
                }
                minor.At(j - 1, k - decrease) = _matrix[j][k];
            }

        }
        determinant += std::pow(T(-1), 2 + i) * _matrix[0][i] * minor.Determinant();
    }

    return determinant;
}

template <typename T>
Linear::Matrix<T> Linear::Matrix<T>::Transpose() const {
    std::vector<std::vector<T>> new_matrix(_columns, std::vector<T>(_rows, T()));
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            new_matrix[j][i] = _matrix[i][j];
        }
    }

    return Matrix<T>(new_matrix);
}

template <typename T>
std::pair<size_t, size_t> Linear::Matrix<T>::Size() const {
    return {_rows, _columns};
}


template <typename T>
Linear::Matrix<T> Linear::Matrix<T>::operator+(const Matrix<T> &m) const {
    if (m.Size() != Size()) throw  Linear::IncompatibleSize("Cannot add matrixes with different sizes");

    Matrix<T> new_matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            new_matrix.At(i, j) = Sel(i, j) + m.Sel(i, j);
        }
    }

    return new_matrix;
}

template <typename T>
Linear::Matrix<T> Linear::Matrix<T>::operator-(const Matrix<T> &m) const {
    return *this + T(-1) * m;
}

template <typename T>
Linear::Matrix<T> Linear::Matrix<T>::operator*(T number) const {
    Matrix<T> new_matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            new_matrix.At(i, j) = Sel(i, j) * number;
        }
    }

    return new_matrix;
}

template <typename T>
Linear::Matrix<T> Linear::Matrix<T>::dot(const Matrix<T> &m) const {
    auto size = m.Size();
    if (_columns != size.first) throw Linear::IncompatibleSize("Can't multiply matrix when columns of the first one (" +
                                                               std::to_string(_columns) +
                                                               ") do not equal to rows of the second (" +
                                                               std::to_string(size.first) + ")!");
    Matrix<T> new_matrix(_rows, size.second);
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            for (size_t k = 0; k < _columns; ++k) {
                new_matrix.At(i, j) += Sel(i, k) * m.Sel(k, j);
            }
            if (fabs(new_matrix.Sel(i, j)) < Linear::epsilon) new_matrix.At(i, j) = T(0);
        }
    }

    return new_matrix;
}

template <typename T>
bool Linear::Matrix<T>::operator==(const Matrix<T> &m) const {
    if (Size() != m.Size()) return false;

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            if (fabs(Sel(i, j) - m.Sel(i, j)) > Linear::epsilon) return false;
        }
    }

    return true;
}


template <typename T>
Linear::Matrix<T> Linear::Matrix<T>::operator*(const Matrix<T> &m) const {
    if (Size() != m.Size()) throw Linear::IncompatibleSize("Sizes are incompatible, cannot do the "
                                                           "componentwise multiplication");

    Matrix<T> new_matrix(_rows, _columns);

    for (size_t i = 0; i < _rows; ++i){
        for (size_t j = 0; j < _columns; ++j) {
            new_matrix.At(i, j) = Sel(i, j) * m.Sel(i, j);
        }
    }

    return new_matrix;
}

template <typename T>
Linear::Diagonal<T>::Diagonal(const std::vector<std::vector<T>>& matrix) : Matrix<T>(matrix) {
    if (Matrix<T>::_rows != Matrix<T>::_columns) throw Linear::IncompatibleSize("Diagonal matrix "
                                                                                "must be quadratic");
    for (size_t i = 0; i < Matrix<T>::_rows; ++i){
        for (size_t j = 0; j < Matrix<T>::_columns; ++j) {
            if (i == j) continue;
            if (Matrix<T>::_matrix[i][j] != 0) throw Linear::WrongFormat("Diagonal matrix elements which does "
                                                                         "not belong to the diagonal must be zeros ");
        }
    }
}

template <typename T>
Linear::Diagonal<T>::Diagonal(const std::vector<T>& diagonal) : Matrix<T>(diagonal.size()) {
    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        Matrix<T>::At(i, i) = diagonal[i];
    }
}

template <typename T>
T& Linear::Diagonal<T>::At(size_t i, size_t j) {
    if (i != j) throw Linear::OutOfRange("You can't change not diagonal elements in diagonal matrix");
    return Matrix<T>::At(i, j);
}

template <typename T>
T& Linear::Diagonal<T>::At(size_t i) {
    return Matrix<T>::At(i, i);
}

template <typename T>
T Linear::Diagonal<T>::Determinant() const {
    T determinant = 1;
    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        determinant *= Matrix<T>::Sel(i, i);
    }

    return determinant;
}

template <typename T>
T Linear::UpperTriangular<T>::Determinant() const {
    if (Matrix<T>::_rows != Matrix<T>::_columns) throw Linear::WrongFormat("Determinant can only be calculated "
                                                                           "for square matrix.");
    T determinant = 1;
    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        determinant *= Matrix<T>::Sel(i, i);
    }

    return determinant;
}

template <typename T>
[[maybe_unused]] Linear::Diagonal<T>::Diagonal(int N) : Matrix<T>(N) {
    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        Matrix<T>::At(i, i) = T(1);
    }
}

template <typename T>
Linear::Unit<T>::Unit(int N) : Diagonal<T>(N) {}

template <typename T>
T Linear::Unit<T>::Determinant() const {
    return T(1);
}

template <typename T>
Linear::UpperTriangular<T>::UpperTriangular(const std::vector<std::vector<T>>& matrix) : Matrix<T>(matrix) {
    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        for (size_t j = 0; j < i && j < Matrix<T>::_columns; ++j) {
            if (Matrix<T>::_matrix[i][j] != T(0)) throw Linear::OutOfRange("Upper triangular matrix cannot have "
                                                                           "non zero elements below the diagonal");
        }
    }
}

template <typename T>
T& Linear::UpperTriangular<T>::At(size_t i, size_t j) {
    if (i > j) throw Linear::OutOfRange("Cannot access the elements below the diagonal "
                                        "in the upper triangular matrix");
    return Matrix<T>::At(i, j);
}

template <typename T>
Linear::LowerTriangular<T>::LowerTriangular(const std::vector<std::vector<T>>& matrix) : Matrix<T>(matrix) {
    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        for (size_t j = i + 1; j < Matrix<T>::_columns; ++j) {
            if (Matrix<T>::_matrix[i][j] != T(0)) throw Linear::OutOfRange("Lower triangular matrix cannot have "
                                                                           "non zero elements above the diagonal");
        }
    }
}

template <typename T>
T& Linear::LowerTriangular<T>::At(size_t i, size_t j) {
    if (i < j) throw Linear::OutOfRange("Cannot access the elements above the diagonal "
                                        "in the lower triangular matrix");
    return Matrix<T>::At(i, j);
}

template <typename T>
Linear::SymmetricMatrix<T>::SymmetricMatrix(const std::vector<std::vector<T>>& matrix) : Matrix<T>(matrix) {
    if (Matrix<T>::_rows != Matrix<T>::_columns) throw Linear::WrongFormat("Symmetric matrix must be squared");

    for (size_t i = 0; i < Matrix<T>::_rows; ++i) {
        for (size_t j = 0; j < i && j < Matrix<T>::_columns; ++j) {
            if (Matrix<T>::_matrix[i][j] != Matrix<T>::_matrix[j][i]) {
                throw Linear::WrongFormat("Initial matrix is not symmetric");
            }
        }
    }
}

template <typename T>
T Linear::Matrix<T>::Track() const {
    if (_rows != _columns) throw Linear::IncompatibleSize("Track for not square matrix is not defined");
    T result(0);

    for (size_t i = 0; i < _rows && i < _columns; ++i) {
        result += Sel(i, i);
    }

    return result;
}

template <typename T>
double Linear::Matrix<T>::Norm(const Linear::NormType& type) const {
    if (type == NormType::Euclidean) {
        return pow((*this * (*this)).Sum(),
                0.5);
    }

    if (type == NormType::Max) {
        T max = 0;
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _columns; ++j) {
                if (abs(Sel(i, j)) > max) max = abs(Sel(i, j));
            }
        }

        return max;
    }

    return 0;
}

template <typename T>
T Linear::Matrix<T>::Sum() const {
    T sum(0);
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            sum += Sel(i, j);
        }
    }

    return sum;
}

template <typename T>
Linear::Matrix<double> Linear::Matrix<T>::Reverse() const {
    auto det = getUpperTriangularForm().Determinant();
    if (det == 0)
        throw Linear::ZeroDeterminant("Determinant equals to zero. Matrix cannot be reversed");

    Linear::Matrix<double> big_matrix(_rows, _columns * 2);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _rows; ++j) {
            big_matrix.At(i, j) = Sel(i, j);
        }
    };

    for (size_t i = 0; i < _columns; ++i) {
        big_matrix.At(i, _columns + i) = 1;
    }


    int swapsCount = 0;
    for (size_t i = 0; i < _columns && swapsCount < _rows; ++i) {
        double max = big_matrix.Sel(swapsCount, i);
        size_t maxIndex = swapsCount;

        for (size_t row = swapsCount + 1; row < _rows; ++row) {
            if ((big_matrix.Sel(row, i) != 0) && ((max == 0) || (big_matrix.Sel(row, i) > max))) {
                max = big_matrix.Sel(row, i);
                maxIndex = row;
            }
        }

        if (max == 0) continue;

        big_matrix.swapRows(maxIndex, swapsCount++);

        for (size_t j = swapsCount; j < _rows; ++j) {
            double q = big_matrix.Sel(j, i) / big_matrix.Sel(swapsCount - 1, i);
            for (size_t k = 0; k < _columns * 2; ++k) {
                big_matrix.At(j, k) -= big_matrix.Sel(swapsCount - 1, k) * q;
                if (fabs(big_matrix.Sel(j, k)) < Linear::epsilon) big_matrix.At(j, k) = 0;
            }
        }
    }

    for (size_t i = 0; i < _rows; ++i) {
        double general = big_matrix.Sel(i, i);
        for (size_t j = i; j < _columns * 2; ++j) {
            big_matrix.At(i, j) /= general;
        }

        for (size_t j = i; j > 0; --j) {
            double q = big_matrix.Sel(j - 1, i);
            for (size_t k = i; k < _columns * 2; ++k) {
                big_matrix.At(j - 1, k) -= q * big_matrix.Sel(i, k);
                if (fabs(big_matrix.Sel(j - 1, k)) < Linear::epsilon) big_matrix.At(j - 1, k) = 0;
            }
        }
    }

    Linear::Matrix<double> result(_rows, _columns);

    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = _columns; j < _columns * 2; ++j) {
            result.At(i, j - _columns) = big_matrix.Sel(i, j);
        }
    }

    return result;
}

template <typename T>
size_t Linear::Matrix<T>::Rank() const {
    return getUpperTriangularForm().Rank();
}

template <typename T>
size_t Linear::UpperTriangular<T>::Rank() const {
    size_t rank = Matrix<T>::_rows;
    for (size_t i = Matrix<T>::_rows; i > 0; --i) {
        for (size_t j = 0; j < Matrix<T>::_columns; ++j) {
            if (fabs(Matrix<T>::Sel(i - 1, j)) > Linear::epsilon) return rank;
        }
        --rank;
    }

    return rank;
}

template <typename T>
Linear::Matrix<T> Linear::FromFile(const std::string& name) {
    Linear::Matrix<T> m;
    std::ifstream file (name);

    if (!file.is_open()) throw Linear::WrongFormat("Cannot open the file : " + name);
    file >> m;

    file.close();

    return m;
}

template <typename T>
void Linear::Matrix<T>::fromBinary(const std::string &name) {
    std::ifstream rf(name, std::ios::in | std::ios::binary);
    if(!rf) {
        throw Linear::WrongFormat("Cannot open the file : " + name);
    }

    rf.read((char*)&_rows, sizeof(size_t));
    rf.read((char*)&_columns, sizeof(size_t));
    _matrix.resize(_rows, std::vector<T>(_columns));
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            rf.read((char*)&_matrix[i][j], sizeof(T));
        }
    }

    rf.close();

    if(!rf.good()) {
        throw Linear::WrongFormat("Error occurred during reading from file");
    }

}

template <typename T>
void Linear::Matrix<T>::toBinary(const std::string &name) const {
    std::ofstream wf(name, std::ios::out | std::ios::binary);
    if(!wf) {
        throw Linear::WrongFormat("Cannot open the file : " + name);
    }

    wf.write((char*)&_rows, sizeof(size_t));
    wf.write((char*)&_columns, sizeof(size_t));
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _columns; ++j) {
            wf.write((char*)&_matrix[i][j], sizeof(T));
        }
    }

    wf.close();

    if(!wf.good()) {
        throw Linear::WrongFormat("Error occurred during writing to file");
    }
}
