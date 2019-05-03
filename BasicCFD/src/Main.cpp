#include <iostream>
#include "Main.hpp"
#include "Matrix.hpp"

int main() {

    /*
                +                                   +
    Ta = 100C   +-----------------------------------+ Tb = 500C
                +            L = 0.5 m              +
                             A = 10 x 10-3 m^2

                             ap*Tp = aw*Tw + ae*Te + Su
    */

    unsigned int grid = 5;
    double length = 0.5;
    double area = 0.01;
    double Ta = 100;
    double Tb = 500;
    double dx = length / grid;
    double heat = 0;
    double k = 1000;

    OneDDiffusionProblem(grid, k, area, dx, Ta, Tb, heat);

    OneDDiffusionProblem(grid, 0.5, 1, 0.004, 100, 200, 1000000);
    return 0;
}

void OneDDiffusionProblem(const unsigned int &grid, double k, const double &area, const double &dx, const double &Ta, const double &Tb, const double &heat)
{
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
            Su = (heat * area * dx) + (2 * k * area * Ta / dx);
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-ae, i, i + 1);
        }
        else if (i == (grid - 1))
        {
            // last cell
            aw = k * area / dx;
            Sp = -2 * k * area / dx;
            Su = (heat * area * dx) + (2 * k * area * Tb / dx);
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-aw, i, i - 1);
        }
        else
        {
            // inner cells
            aw = k * area / dx;
            ae = aw;
            Su = heat * area * dx;
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-aw, i, i - 1);
            coeffitientMatrix.setValue(-ae, i, i + 1);
        }

        ap = aw + ae - Sp;

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
