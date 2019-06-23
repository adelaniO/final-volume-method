#include <iostream>
#include "Main.hpp"
#include "Matrix.hpp"
#include "Jacobi.hpp"

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

    //OneDDiffusionProblem(grid, k, area, dx, Ta, Tb, heat);
    //OneDDiffusionProblem(5, 0.5, 1, 0.004, 100, 200, 1000000);
    
    //OneDConvectionDiffusionProblem(grid, k, area, dx, Ta, Tb, heat, 0, 0);
    //OneDConvectionDiffusionProblem(5, 0.5, 1, 0.004, 100, 200, 1000000, 0, 0);
    //OneDConvectionDiffusionProblem(5, 0.1, 1, 0.2, 1, 0, 0, 1, 0.1);
    OneDConvectionDiffusionProblem(5, 0.1, 1, 1.0/5.0, 1, 0, 0, 1, 2.5);
    OneDConvectionDiffusionProblem(20, 0.1, 1, 1.0/20.0, 1, 0, 0, 1, 2.5);

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

void OneDConvectionDiffusionProblem(const unsigned int &grid, double k, const double &area, const double &dx, const double &Ta, const double &Tb, const double &heat,
    const double &density, const double &flowRate)
{
    Solver::Matrix solutionVector = Solver::Matrix(grid, 1);
    Solver::Matrix constantVector = Solver::Matrix(grid, 1);
    Solver::Matrix coeffitientMatrix = Solver::Matrix(grid, grid);
    for (size_t i = 0; i < grid; i++)
    {
        // F is the convective mass flux per unit area
        // D is the diffusion conductance at cell faces
        // e and w subscript represent the east and west nodes in adjacent cell
        double aw{}, ae{}, ap{}, Sp{}, Su{};
        const double Fe = density * flowRate * area; 
        const double Fw = Fe;
        const double De = k * area / dx;
        const double Dw = De;
        if (i == 0)
        {
            // first cell
            ae = De - Fe / 2;
            Sp = -(2 * Dw + Fe);
            Su = (heat * area * dx) + ((2 * Dw + Fw) * Ta); // Fw = F at inlet (Fa)
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-ae, i, i + 1);
        }
        else if (i == (grid - 1))
        {
            // last cell
            aw = Dw + Fw / 2;
            Sp = -(2 * De - Fw);
            Su = (heat * area * dx) + ((2 * De - Fe) * Tb); // Fe = F at outlet (Fb)
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-aw, i, i - 1);
        }
        else
        {
            // inner cells
            aw = Dw + Fw / 2;
            ae = De - Fe / 2;
            Su = heat * area * dx;
            // Fill in coefficient matrix
            coeffitientMatrix.setValue(-aw, i, i - 1);
            coeffitientMatrix.setValue(-ae, i, i + 1);
        }

        ap = aw + ae - Sp;

        // Fill in coefficient matrix
        coeffitientMatrix.setValue(ap, i, i);
        // Fill in constant Terms
        constantVector.setValue(Su, i);
    }

    // Solve
    Solver::Jacobi linearSolver(&coeffitientMatrix, &constantVector, &solutionVector, 10000, 1e-5);
    linearSolver.setRelaxation(0.1);
    linearSolver.solve();
    // Print all matrices and vectors
    coeffitientMatrix.print("Coefficient Matrix");
    constantVector.print("Constant Terms");
    solutionVector.print("Solution Vector");
}
