#pragma once
#include "iostream"
#include "Matrix.hpp"

Matrix::Matrix(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
    
    m_matrix = new double*[m_rows]; // allocate an array of double pointers — these are our rows
    for (unsigned int i = 0; i < m_rows; ++i)
    {
        m_matrix[i] = new double[m_cols]; // these are our columns
        memset(m_matrix[i], 0, m_cols * sizeof(double)); // initialise with zeros
    }
}

Matrix::~Matrix()
{
    for (unsigned int row = 0; row < m_rows; ++row)
        delete[] m_matrix[row];
    delete[] m_matrix; // this needs to be done last
}

bool Matrix::setValue(unsigned int row, unsigned int col, double value)
{
    if (row > m_rows - 1)
    {
        std::cout << "Unable to set Matrix value. Matrix has less than " << row + 1 << " rows" << std::endl;
        return false;
    }
    if (col > m_cols - 1)
    {
        std::cout << "Unable to set Matrix value. Matrix has less than " << col + 1 << " colums" << std::endl;
        return false;
    }

    m_matrix[row][col] = value;
    return true;
}

void Matrix::print()
{
    for (unsigned int row = 0; row < m_rows; row++)
    {
        for (unsigned int col = 0; col < m_cols; col++)
            std::cout << m_matrix[row][col] << "\t";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
