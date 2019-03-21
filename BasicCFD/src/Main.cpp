#include <iostream>

int main() {
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
    double solutionMatrix[grid] = { };
    double constantTerms[grid] = { };
    double coeffitientMatrix[grid][grid] = { };
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
            coeffitientMatrix[i][i + 1] = -ae;
        }
        else if (i == (grid - 1))
        {
            // last cell
            aw = k * area / dx;
            Sp = -2 * k * area / dx;
            Su = 2 * k * area * Tb / dx;
            ap = aw + ae - Sp;
            // Fill in coefficient matrix
            coeffitientMatrix[i][i - 1] = -aw;
        }
        else
        {
            // inner cells
            aw = k * area / dx;
            ae = aw;
            ap = aw + ae;
            // Fill in coefficient matrix
            coeffitientMatrix[i][i - 1] = -aw;
            coeffitientMatrix[i][i + 1] = -ae;
        }
        // Fill in coefficient matrix
        coeffitientMatrix[i][i] = ap;
        // Fill in constant Terms
        constantTerms[i] = Su;
    }

    // Print Coefficient Matrix
    std::cout << "Coefficient Matrix" << std::endl;
    for (int i = 0; i < grid; i++)
    {
        for (int j = 0; j < grid; j++)
        {
            std::cout << coeffitientMatrix[i][j] << '\t';
        }
        std::cout << std::endl;
    }

    // Print Constant Terms
    std::cout << "Constant Terms" << std::endl;
    for (int i = 0; i < grid; i++)
    {
        std::cout << constantTerms[i] << std::endl;
    }

    return 0;
}