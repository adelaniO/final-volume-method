#pragma once
#include "Matrix.hpp"

namespace Solver
{
    class Matrix;
    class Jacobi
    {
    public:
        Jacobi(Matrix *A, Matrix *B, Matrix *X, const size_t maxIterations, const double convergenceCriterion);
        void setRelaxation(const double relaxationNumber) { relaxationNo = relaxationNumber; };
        void solve();

    private:
        Matrix *m_A, *m_B, *m_X;
        size_t m_maxIterations{};
        size_t m_numIterations{};
        double m_convergenceCriterion{1e-6};
        double m_divergenceCriterion{1e6};
        double m_residual{ 1e6 };
        double relaxationNo{ 1 };
        bool m_converged{ false };
        bool m_diverged{ false };
    };
}