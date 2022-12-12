#include "operator.h"
#include "exception.h"
#include <sstream>
#include <cmath>
#include <iomanip>

template <typename T>
std::ostream& operator<< (std::ostream& os, const Linear::Matrix<T>& matrix) {
    std::pair<size_t, size_t> size = matrix.Size();

//    os << "[";
    if (size.first == 0) {
//        os << "[]]";
        return os;
    }
    for (size_t i = 0; i < size.first; ++i) {
//        os << "[";
        for (size_t j = 0; j < size.second; ++j) {
            if (j != 0) {
                os << ", " << std::setw(6);
            }
            os  << matrix.Sel(i, j);
        }
        if (i != size.first - 1) {
//            os << "],\n";
            os << '\n';
        }
//        else {
//            os << "]]";
//        }
    }

    return os;
}

template <typename T>
std::istream& operator>> (std::istream& is, Linear::Matrix<T>& m) {
    std::string line;
    size_t columns = 0;

    bool first_line = true;

    std::vector<std::vector<T>> matrix;

    while (getline(is, line)) {
        size_t i = 0;
        std::vector<T> row;
        std::istringstream ss(line);
        T num;
        while (ss >> num) {
            ++i;
            row.push_back(num);
        }

        if (first_line) {
            columns = i;
            first_line = false;
        }

        if (i != columns) {
            throw Linear::WrongFormat("Check the correctness of the matrix in input stream given.");
        }

        matrix.push_back(row);
    }

    m = Linear::Matrix<T>(matrix);

    return is;

}

template <typename T>
Linear::Matrix<T> operator* (T number, const Linear::Matrix<T>& matrix) {
    auto size = matrix.Size();
    Linear::Matrix <T> new_matrix(size.first, size.second);

    for (size_t i = 0; i < size.first; ++i) {
        for (size_t j = 0; j < size.second; ++j) {
            new_matrix.At(i, j) = matrix.Sel(i, j) * number;
        }
    }

    return new_matrix;
}

template <typename T, typename D>
bool operator== (const Linear::Matrix<T>& m1, const Linear::Matrix<D>& m2) {
    auto m1_size = m1.Size();
    if (m1_size != m2.Size()) return false;

    for (size_t i = 0; i < m1_size.first; ++i) {
        for (size_t j = 0; j < m1_size.second; ++j) {
            if (fabs(m1.Sel(i, j) - m2.Sel(i, j)) > Linear::epsilon) return false;
        }
    }

    return true;
}

template <typename T, typename D>
Linear::Matrix<T> operator+ (const Linear::Matrix<T>& m1, const Linear::Matrix<D>& m2) {
    auto m1_size = m1.Size();
    if (m1_size != m2.Size()) throw  Linear::IncompatibleSize("Cannot add matrixes with different sizes");

    Linear::Matrix<T> new_matrix(m1_size.first, m1_size.second);

    for (size_t i = 0; i < m1_size.first; ++i) {
        for (size_t j = 0; j < m1_size.second; ++j) {
            new_matrix.At(i, j) = m1.Sel(i, j) + T(m2.Sel(i, j));
        }
    }

    return new_matrix;
}

template <typename T, typename D>
Linear::Matrix<T> operator- (const Linear::Matrix<T>& m1, const Linear::Matrix<D>& m2) {
    return m1 + D(-1) * m2;
}

template <typename T>
double operator^(const Linear::Matrix<T>& vector1, const Linear::Matrix<T>& vector2) {
    auto vec1_size = vector1.Size();
    auto vec2_size = vector2.Size();
    if ((vec1_size.first != 1 && vec1_size.second != 1) || (vec2_size.first != 1 && vec2_size.second != 1))
        throw Linear::IncompatibleSize("Cannot calculate the angle of not vector objects");

    double scalar;
    if (vec1_size.first == vec1_size.first) {
        scalar = (vector1 * vector2).Sum();
    } else {
        scalar = (vector1 * vector2.Transpose()).At(0, 0);
    }

    if (scalar - 0 < Linear::epsilon) return 1;

    return acos(scalar / (vector1.Norm() * vector2.Norm()));
}
