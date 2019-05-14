#pragma once

void OneDDiffusionProblem(const unsigned int &grid, double k, const double &area, const double &dx, const double &Ta, const double &Tb, const double &heat);
void OneDConvectionDiffusionProblem(const unsigned int &grid, double k, const double &area, const double &dx, const double &Ta, const double &Tb, const double &heat,
    const double &density, const double &flowRate);
