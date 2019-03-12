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

    for (size_t i = 0; i < grid; i++)
    {
        double aw = 0, ae = 0, ap = 0, Sp = 0, Su = 0;
        if(i == 0)
        {
            // first cell
            ae = k * area / dx;
            Sp = -2 * k* area / dx;
            Su = 2 * k * area * Ta / dx;
            ap = aw + ae - Sp;
            std::cout << ap << " T" << i << " = " << ae << " T" << i + 1 << " + " << Su << " Ta" << std::endl;
        }
        else if (i == (grid - 1))
        {
            // last cell
            aw = k * area / dx;
            Sp = -2 * k * area / dx;
            Su = 2 * k * area * Tb / dx;
            ap = aw + ae - Sp;
            std::cout << ap << " T" << i << " = " << aw << " T" << i - 1 << " + " << Su << " Tb" << std::endl;
        }
        else
        {
            // inner cells
            aw = k * area / dx;
            ae = aw;
            ap = aw + ae;
            std::cout << ap << " T"<<i << " = " << aw << " T"<<i-1 << " + " << ae << " T"<<i+1 <<std::endl;
        }
    }
    std::cin >> k;

}