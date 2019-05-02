#include "stdafx.h"
#include "iostream"
#include "Matrix.hpp"

namespace Solver
{
    Matrix::Matrix()
    {
    }

    Matrix::Matrix(std::size_t rows, std::size_t cols, const std::vector<double> &data)
    {
        m_rows = rows;
        m_cols = cols;

        if(data.size() > 0)
            m_matrix = data;
        else
            m_matrix = std::vector<double>(rows * cols, 0);
    }

    double Matrix::rmsMatrixElements()
    {
        double square{};
        // Calculate square.
        for(const double element : m_matrix)
            square += std::pow(element, 2);

        return std::sqrt(square / m_matrix.size());
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

    void Matrix::resizeMarix(std::size_t rows, std::size_t cols, std::vector<double> const &data)
    {
        m_rows = rows;
        m_cols = cols;
        m_matrix.resize(rows * cols);
        if(data.size() > 0)
            m_matrix = data;
    }

    void Matrix::addOrSubtract(const Matrix &input, const bool add)
    {
        if (m_rows != input.getRowSize() && m_cols != input.getColSize())
            throw std::invalid_argument("Matrices can only be added or subtracted if they are of the same order");

        for (std::size_t i = 0; i < m_rows; i++)
        {
            for (std::size_t j = 0; j < m_cols; j++)
            {
                if (add)
                    m_matrix[getIndexFromRowAndCol(i, j)] += input.getValue(i, j);
                else
                    m_matrix[getIndexFromRowAndCol(i, j)] -= input.getValue(i, j);
            }
        }
    }

    Matrix Matrix::dot(const Matrix& input) const
    {
        if (m_cols != input.getRowSize())
            throw std::invalid_argument("Dot Product is defined only when the number of columns in the first matrix equals the number of rows in the second");

        double tempVal{};
        std::size_t newCols = input.getColSize();

        Matrix result(m_rows, newCols);
        result.resizeMarix(m_rows, newCols);
        for (std::size_t i = 0; i < m_rows; i++)
        {
            for (std::size_t j = 0; j < newCols; j++)
            {
                for (std::size_t k = 0; k < m_cols; k++)
                {
                    tempVal += getValue(i, k) * input.getValue(k, j);
                }
                result.setValue(tempVal, i, j);
                tempVal = 0;
            }
        }
        return result;
    }

    bool Matrix::operator==(const Matrix &other) const
    {
        return 
            m_rows == other.m_rows &&
            m_cols == other.m_cols &&
            m_matrix == other.m_matrix;
    }

    bool Matrix::operator!=(const Matrix &other) const
    {
        return !(*this == other);
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

    Matrix operator-(const Matrix & lhs, const Matrix & rhs)
    {
        Matrix result = lhs;
        result.subtract(rhs);
        return result;
    }

    Matrix operator+(const Matrix & lhs, const Matrix & rhs)
    {
        Matrix result = lhs;
        result.add(rhs);
        return result;
    }

    Matrix operator*(const Matrix & lhs, const Matrix & rhs)
    {
        return lhs.dot(rhs);
    }

    Matrix operator*(const Matrix & lhs, const double rhs)
    {
        Matrix result = lhs;
        result.multiplyBy(rhs);
        return result;
    }
}
