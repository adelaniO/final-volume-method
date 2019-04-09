#pragma once
#include <vector>
#include <string>
namespace Solver
{
    class Matrix {
    private:
        unsigned int m_rows{};
        unsigned int m_cols{};
        double** m_matrix;
    public:
        Matrix(int rows, int cols);
        ~Matrix();

        double getValue(int row, int col = 0) { return m_matrix[row][col]; };
        unsigned int getColSize() { return m_cols; };
        unsigned int getRowSize() { return m_rows; };
        double** getMatrix() { return m_matrix; };

        bool setValue(double value, unsigned int row, unsigned int col = 0);
        void add(Matrix* const input) { addOrSubtract(input, true); };
        void subtract(Matrix* const input) { addOrSubtract(input, false); };
        void addOrSubtract(Matrix* const input, const bool add);
        void multiplyBy(const double input);
        void dot(Matrix* const input);
        void print(std::string title = "");
    };
}
