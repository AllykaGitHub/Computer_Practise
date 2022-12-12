#ifndef LINEAR_LINEAR_H
#define LINEAR_LINEAR_H

#define LINEAR_API __declspec(dllexport)

#include <vector>
#include <string>

namespace Linear {
    const static double epsilon = 0.00000001;
    enum NormType {
        Euclidean,
        Max
    };

    template<typename T>
    class Matrix;

    template<typename T>
    class UpperTriangular;

    template<typename T>
    class Matrix {
    public:

        Matrix(std::initializer_list<std::initializer_list<T>> _list);
        explicit Matrix(const std::vector<std::vector<T>> &);

        explicit Matrix(const std::vector<T> &);

        Matrix(int, int);

        explicit Matrix(int);

        Matrix();

        void swapRows(size_t i, size_t j);

        [[nodiscard]] Linear::UpperTriangular<double> getUpperTriangularForm() const;


        virtual T &At(size_t i, size_t j);
        T Sel(size_t i, size_t j) const;
        [[nodiscard]] std::pair<size_t, size_t> Size() const;
        T Sum() const;
        Linear::Matrix<T> Transpose() const;
        [[nodiscard]] Linear::Matrix<double> Reverse() const;
        virtual T Determinant() const;
        std::vector<std::vector<T>> getExplicit() const;
        T Track() const;
        [[nodiscard]] double Norm(const Linear::NormType& type = Linear::NormType::Euclidean) const;
        [[nodiscard]] virtual size_t Rank() const;


        Linear::Matrix<T> operator+(const Matrix<T> &m) const;
        Linear::Matrix<T> operator-(const Matrix<T> &m) const;
        bool operator==(const Matrix<T> &m) const;
        Linear::Matrix<T> operator*(T number) const;
        Linear::Matrix<T> dot(const Matrix<T> &m) const;
        Linear::Matrix<T> operator*(const Matrix<T> &m) const;

        void toBinary(const std::string& name) const;
        void fromBinary(const std::string& name);

    protected:
        std::vector<std::vector<T>> _matrix;
        size_t _rows, _columns;
    };

    template<typename T>
    class Diagonal : public Matrix<T> {
    public:
        explicit Diagonal(const std::vector<std::vector<T>> &);

        explicit Diagonal(const std::vector<T> &);

        T &At(size_t i, size_t j) override;

        virtual T &At(size_t i);

        T Determinant() const override;

        [[maybe_unused]] explicit Diagonal(int);
    };

    template<typename T>
    class Unit : public Diagonal<T> {
    public:
        explicit Unit(int);

        T Determinant() const override;

    private:
        using Diagonal<T>::At;
    };

    template<typename T>
    class UpperTriangular : public Matrix<T> {
    public:
        explicit UpperTriangular(const std::vector<std::vector<T>> &matrix);

        T &At(size_t i, size_t j) override;

        T Determinant() const override;

        [[nodiscard]] size_t Rank() const override;

    private:
        using Matrix<T>::swapRows;
    };

    template<typename T>
    class LowerTriangular : public Matrix<T> {
    public:
        explicit LowerTriangular(const std::vector<std::vector<T>> &matrix);

        T &At(size_t i, size_t j) override;

    private:
        using Matrix<T>::swapRows;
    };

    template<typename T>
    class SymmetricMatrix : public Matrix<T> {
    public:
        explicit SymmetricMatrix(const std::vector<std::vector<T>> &matrix);

    private:
        using Matrix<T>::At;
        using Matrix<T>::swapRows;
    };

    template <typename T>
    Linear::Matrix<T> FromFile(const std::string& name);

}


#endif //LINEAR_LINEAR_H
