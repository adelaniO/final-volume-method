#pragma once
#include <vector>
#include <string>
namespace Solver
{
    class Matrix {
    private:
        int m_rows{-1};
        int m_cols{-1};
        double** m_matrix;
        void init(int rows, int cols);
        void deleteMarix();
    public:
        Matrix();
        Matrix(int rows, int cols);
        ~Matrix();

        double getValue(int row, int col = 0) const { return m_matrix[row][col]; };
        int getColSize() const { return m_cols; };
        int getRowSize() const { return m_rows; };
        double** getMatrix() { return m_matrix; };

        bool setValue(double value, int row, int col = 0);
        void resizeMarix(int rows, int cols);
        void add(Matrix* const input) { addOrSubtract(input, true); };
        void subtract(Matrix* const input) { addOrSubtract(input, false); };
        void addOrSubtract(Matrix* const input, const bool add);
        void multiplyBy(const double input);
        void dot(const Matrix& input, Matrix* result) const;
        void print(std::string title = "");
    };
}
