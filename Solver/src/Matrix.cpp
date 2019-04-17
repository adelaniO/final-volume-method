#pragma once
#include "stdafx.h"
#include "iostream"
#include "Matrix.hpp"

namespace Solver
{
    Matrix::Matrix()
    {
    }

    Matrix::Matrix(int rows, int cols)
    {
        init(rows, cols);
    }

    void Matrix::init(int rows, int cols)
    {
        m_rows = rows;
        m_cols = cols;

        m_matrix = new double*[rows]; // allocate an array of double pointers — these are our rows
        for (int i = 0; i < m_rows; ++i)
        {
            m_matrix[i] = new double[cols](); // these are our columns initialised with zeros
        }
    }

    Matrix::~Matrix()
    {
        deleteMarix();
    }

    void Matrix::deleteMarix()
    {
        if (m_rows < 0 || m_cols < 0)
            return;

        for (int row = 0; row < m_rows; ++row)
            delete[] m_matrix[row];
        delete[] m_matrix; // this needs to be done last
        m_rows = 0;
        m_cols = 0;
    }

    void Matrix::resizeMarix(int rows, int cols)
    {
        deleteMarix();
        init(rows, cols);
    }

    bool Matrix::setValue(double value, int row, int col)
    {
        if (row > m_rows - 1)
        {
            // TODO: Throw a proper error here
            std::cout << "Unable to set Matrix value. Matrix has less than " << row + 1 << " rows" << std::endl;
            return false;
        }
        if (col > m_cols - 1)
        {
            // TODO: Throw a proper error here
            std::cout << "Unable to set Matrix value. Matrix has less than " << col + 1 << " colums" << std::endl;
            return false;
        }

        m_matrix[row][col] = value;
        return true;
    }

    void Matrix::addOrSubtract(Matrix* const input, const bool add)
    {
        if (m_rows != input->getRowSize() && m_cols != input->getColSize())
            throw std::invalid_argument("Matrices can only be added or subtracted if they are of the same order");

        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < m_cols; j++)
            {
                if (add)
                    m_matrix[i][j] += input->getValue(i, j);
                else
                    m_matrix[i][j] -= input->getValue(i, j);
            }
        }
    }

    void Matrix::dot(const Matrix& input, Matrix* result) const
    {
        if (m_cols != input.getRowSize())
            throw std::invalid_argument("Dot Product is defined only when the number of columns in the first matrix equals the number of rows in the second");

        double tempVal{};
        int newCols = input.getColSize();

        result->resizeMarix(m_rows, newCols);
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < newCols; j++)
            {
                for (int k = 0; k < m_cols; k++)
                {
                    tempVal += getValue(i, k) * input.getValue(k, j);
                }
                result->setValue(tempVal, i, j);
                tempVal = 0;
            }
        }
    }

    void Matrix::multiplyBy(const double input)
    {
        for (int i = 0; i < m_rows; i++)
        {
            for (int j = 0; j < m_cols; j++)
                m_matrix[i][j] *= input;
        }
    }

    void Matrix::print(std::string title)
    {
        std::cout << title << std::endl;
        for (int row = 0; row < m_rows; row++)
        {
            for (int col = 0; col < m_cols; col++)
                std::cout << m_matrix[row][col] << "\t";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
