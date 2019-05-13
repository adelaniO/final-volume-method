#include "stdafx.h"
#include "Jacobi.hpp"
#include <numeric>

namespace Solver
{
    Jacobi::Jacobi(Matrix *A, Matrix *B, Matrix *X, const size_t maxIt, const double convergenceCrit) : m_A(A), m_B(B), m_X(X), m_maxIterations(maxIt), m_convergenceCriterion(convergenceCrit)
    {
    }

    void Jacobi::solve()
    {
        /*
        * Solve a linear system of equations where A.X = B
        * Here X is the initial guess
        * Jacobi iteration method: X(it) = T.X(it-1) + C
        * There T is the Iteration matrix and C is the constant vector
        */

        // Create the Iteration matrix
        Matrix T = Matrix(m_A->getRowSize(), m_A->getColSize());
        // Create the constant vector
        Matrix C = Matrix(m_A->getRowSize(), 1);
        // Populate in iteration matrix and constant vector
        for (std::size_t i = 0; i < m_A->getRowSize(); i++)
        {
            C.setValue(relaxationNo * m_B->getValue(i) / m_A->getValue(i, i), i);
            for (std::size_t j = 0; j < m_A->getColSize(); j++)
            {
                double tempValue{ 1 - relaxationNo };
                if (i != j)
                    tempValue = -relaxationNo * m_A->getValue(i, j) / m_A->getValue(i, i);
                T.setValue(tempValue, i, j);
            }
        }

        //Solve
        m_numIterations = 0;
        Matrix residualMatrix = Matrix(m_A->getRowSize(), 1);
        while (m_numIterations < m_maxIterations)
        {
            //Get new solution vector
            *m_X = T * (*m_X) + C;
            //Generate residual vector and sum to get reidual value
            residualMatrix = (*m_B) - (*m_A) * (*m_X);
            m_residual = residualMatrix.rmsMatrixElements();

            if (m_residual <= m_convergenceCriterion)
            {
                m_converged = true;
                break;
            }
            else if (m_residual >= m_divergenceCriterion || isinf(m_residual))
            {
                m_diverged = true;
                break;
            }
            m_numIterations++;
        }
    }
}