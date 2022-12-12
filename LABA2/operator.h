#ifndef LINEAR_OPERATOR_H
#define LINEAR_OPERATOR_H

#include <iostream>
#include "linear.h"

template <typename T>
std::ostream& operator<< (std::ostream& os, const Linear::Matrix<T>& matrix);

template <typename T>
std::istream& operator>> (std::istream& is, Linear::Matrix<T>& m);

template <typename T>
Linear::Matrix<T> operator* (T number, const Linear::Matrix<T>& matrix);

template <typename T, typename D>
bool operator== (const Linear::Matrix<T>& m1, const Linear::Matrix<D>& m2);

template <typename T, typename D>
Linear::Matrix<T> operator+ (const Linear::Matrix<T>& m1, const Linear::Matrix<D>& m2);

template <typename T, typename D>
Linear::Matrix<T> operator- (const Linear::Matrix<T>& m1, const Linear::Matrix<D>& m2);


template <typename T, typename D>
double operator^(const Linear::Matrix<T>& vector1, const Linear::Matrix<T>& vector2);


#endif //LINEAR_OPERATOR_H
