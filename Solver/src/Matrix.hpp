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
        void init(std::size_t rows, std::size_t cols);
    public:
        Matrix();
        Matrix(std::size_t rows, std::size_t cols);
        Matrix(std::size_t rows, std::size_t cols, std::vector<double> const &array);

        double getValue(std::size_t row, std::size_t col = 0) const { return m_matrix[getIndexFromRowAndCol(row, col)]; };
        std::size_t getColSize() const { return m_cols; };
        std::size_t getRowSize() const { return m_rows; };
        std::vector<double> getMatrix() { return m_matrix; };
        std::size_t getIndexFromRowAndCol(std::size_t row, std::size_t col = 0) const;

        bool setValue(double value, std::size_t row, std::size_t col = 0);

        void resizeMarix(std::size_t rows, std::size_t cols);

        void add(Matrix* const input) { addOrSubtract(input, true); };
        void subtract(Matrix* const input) { addOrSubtract(input, false); };
        void addOrSubtract(Matrix* const input, const bool add);
        void multiplyBy(const double input);
        void dot(const Matrix& input, Matrix* result) const;

        void print(std::string title = "");
    };
}
