#pragma once
#include "Matrix.hpp"

namespace Solver
{
    class Matrix;
    class Jacobi
    {
    public:
        Jacobi(Matrix *A, Matrix *B, Matrix *X, const size_t maxIterations, const double convergenceCriterion);
        void solve();

    private:
        Matrix *m_A, *m_B, *m_X;
        size_t m_maxIterations{};
        size_t m_numIterations{};
        double m_convergenceCriterion{0.000001};
        double m_residual{ 1e6 };
    };
}