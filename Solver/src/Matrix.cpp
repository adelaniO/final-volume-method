#pragma once
#include "stdafx.h"
#include "iostream"
#include "Matrix.hpp"

namespace Solver
{
    Matrix::Matrix()
    {
    }

    Matrix::Matrix(std::size_t rows, std::size_t cols)
    {
        init(rows, cols);
    }

    Matrix::Matrix(std::size_t rows, std::size_t cols, std::vector<double> const & array)
    {
        if (array.size() != rows * cols)
            throw std::invalid_argument("Size of initialising array must equal to the multiple of the row and col parameters.");
        if (array.size() == 0)
            throw std::invalid_argument("Size of initialising array must be greater than 0.");
        m_rows = rows;
        m_cols = cols;
        m_matrix = array;
    }

    void Matrix::init(std::size_t rows, std::size_t cols)
    {
        m_rows = rows;
        m_cols = cols;
        m_matrix = std::vector<double>(rows * cols, 0);
    }

    std::size_t Matrix::getIndexFromRowAndCol(std::size_t row, std::size_t col) const
    {
        return m_cols * row + col;
    }

    bool Matrix::setValue(double value, std::size_t row, std::size_t col)
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

        m_matrix[getIndexFromRowAndCol(row, col)] = value;
        return true;
    }

    void Matrix::resizeMarix(std::size_t rows, std::size_t cols)
    {
        m_rows = rows;
        m_cols = cols;
        m_matrix.resize(rows * cols);
    }

    void Matrix::addOrSubtract(Matrix* const input, const bool add)
    {
        if (m_rows != input->getRowSize() && m_cols != input->getColSize())
            throw std::invalid_argument("Matrices can only be added or subtracted if they are of the same order");

        for (std::size_t i = 0; i < m_rows; i++)
        {
            for (std::size_t j = 0; j < m_cols; j++)
            {
                if (add)
                    m_matrix[getIndexFromRowAndCol(i, j)] += input->getValue(i, j);
                else
                    m_matrix[getIndexFromRowAndCol(i, j)] -= input->getValue(i, j);
            }
        }
    }

    void Matrix::dot(const Matrix& input, Matrix* result) const
    {
        if (m_cols != input.getRowSize())
            throw std::invalid_argument("Dot Product is defined only when the number of columns in the first matrix equals the number of rows in the second");

        double tempVal{};
        std::size_t newCols = input.getColSize();

        result->resizeMarix(m_rows, newCols);
        for (std::size_t i = 0; i < m_rows; i++)
        {
            for (std::size_t j = 0; j < newCols; j++)
            {
                for (std::size_t k = 0; k < m_cols; k++)
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
        for (std::size_t i = 0; i < m_rows; i++)
        {
            for (std::size_t j = 0; j < m_cols; j++)
                m_matrix[getIndexFromRowAndCol(i, j)] *= input;
        }
    }

    void Matrix::print(std::string title)
    {
        std::cout << title << std::endl;
        for (std::size_t row = 0; row < m_rows; row++)
        {
            for (std::size_t col = 0; col < m_cols; col++)
                std::cout << m_matrix[getIndexFromRowAndCol(row, col)] << "\t";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}
