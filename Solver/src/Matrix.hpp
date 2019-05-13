#pragma once
#include <vector>
#include <string>
namespace Solver
{
    class Matrix {
    private:
        std::size_t m_rows{};
        std::size_t m_cols{};
        std::vector<double> m_matrix;

    public:
        Matrix();
        Matrix(std::size_t rows, std::size_t cols, const std::vector<double> &data = {});

        bool isDiagonallyDominant();

        double getValue(std::size_t row, std::size_t col = 0) const { return m_matrix[getIndexFromRowAndCol(row, col)]; };
        double rmsMatrixElements();
        std::size_t getColSize() const { return m_cols; };
        std::size_t getRowSize() const { return m_rows; };
        std::vector<double> getMatrix() { return m_matrix; };
        std::size_t getIndexFromRowAndCol(std::size_t row, std::size_t col = 0) const;

        bool setValue(double value, std::size_t row, std::size_t col = 0);

        void resizeMarix(std::size_t rows, std::size_t cols, const std::vector<double> &data = {});

        void add(const Matrix &input) { addOrSubtract(input, true); };
        void subtract(const Matrix &input) { addOrSubtract(input, false); };
        void addOrSubtract(const Matrix &input, const bool add);
        void multiplyBy(const double input);

        Matrix dot(const Matrix& input) const;
        bool operator==(const Matrix &other) const;
        bool operator!=(const Matrix &other) const;

        friend Matrix operator-(const Matrix &lhs, const Matrix &rhs);
        friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);
        friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);
        friend Matrix operator*(const Matrix &lhs, const double rhs);
        friend Matrix operator*(const double lhs, const Matrix &rhs) { return rhs * lhs; };

        void print(std::string title = "");
    };
}
