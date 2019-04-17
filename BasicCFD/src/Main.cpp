#include <iostream>
#include "Main.hpp"
#include "Matrix.hpp"

int main() {
    OneDDiffusionProblem();
    return 0;
}

void OneDDiffusionProblem()
{

    /*
                +                                   +
    Ta = 100C   +-----------------------------------+ Tb = 500C
                +            L = 0.5 m              +
                             A = 10 x 10-3 m^2

                             ap*Tp = aw*Tw + ae*Te + Su
    */

    const unsigned int grid = 5;
    const double length = 0.5;
    const double area = 0.01;
    const double Ta = 100;
    const double Tb = 500;
    const double dx = length / grid;
    double k = 1000;

    Solver::Matrix solutionMatrix = Solver::Matrix(grid, 1);
    Solver::Matrix constantTerms = Solver::Matrix(grid, 1);
    Solver::Matrix coeffitientMatrix = Solver::Matrix(grid, grid);
    for (size_t i = 0; i < grid; i++)
    {
        double aw = 0, ae = 0, ap = 0, Sp = 0, Su = 0;
        if (i == 0)
        {
            // first cell
            ae = k * area / dx;
            Sp = -2 * k* area / dx;
            Su = 2 * k * area * Ta / dx;
            ap = aw + ae - Sp;
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-ae, i, i + 1);
        }
        else if (i == (grid - 1))
        {
            // last cell
            aw = k * area / dx;
            Sp = -2 * k * area / dx;
            Su = 2 * k * area * Tb / dx;
            ap = aw + ae - Sp;
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-aw, i, i - 1);
        }
        else
        {
            // inner cells
            aw = k * area / dx;
            ae = aw;
            ap = aw + ae;
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-aw, i, i - 1);
            coeffitientMatrix.setValue(-ae, i, i + 1);
        }
        // Fill in coefficient matrix
        coeffitientMatrix.setValue(ap, i, i);
        // Fill in constant Terms
        constantTerms.setValue(Su, i);
    }

    // Print Coefficient Matrix
    coeffitientMatrix.print("Coefficient Matrix");

    // Print Constant Terms
    constantTerms.print("Constant Terms");
}