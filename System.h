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
    System(const std::vector<Variable>& v);
    std::vector<Point> evaluate_points(std::vector<Variable>& variables, int x_index, double step);
    std::vector<Variable> variables;
};


#endif //PARAPLOT_SYSTEM_H
