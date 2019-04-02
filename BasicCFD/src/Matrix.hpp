#pragma once
#include <vector>

class Matrix {
private:
    unsigned int m_rows{};
    unsigned int m_cols{};
    double** m_matrix;
public:
    Matrix(int rows, int cols);
    ~Matrix();

    double getValue(int row, int col) { return m_matrix[row][col];; };
    unsigned int getColSize() { return m_cols; };
    unsigned int getRowSize() { return m_rows; };
    double** getMatrix() { return m_matrix; };

    bool setValue(unsigned int row, unsigned int col, double value);
    void print();
};

