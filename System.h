//
// Created by stefanciutac on 26/06/2026.
//

#ifndef PARAPLOT_SYSTEM_H
#define PARAPLOT_SYSTEM_H

#include <vector>
#include <iostream>
#include <cmath>
#include <random>

#include "Structs.h"

class System
{
private:

public:
    System(const std::vector<Variable>& v, int i, double s);
    Point evaluate_point();
    std::vector<Point> evaluate_points();
    std::vector<Variable> variables;
    int x_index;
    double step;
};


#endif //PARAPLOT_SYSTEM_H
