//
// Created by stefanciutac on 26/06/2026.
//

#include "System.h"
#include "SystemDefinition.h"

System::System(const std::vector<Variable>& v)
    :variables(v)
{
}

std::vector<Point> System::evaluate_points(std::vector<Variable>& variables, int x_index, double step)
{
    std::vector<Point> points;

    for (double x = variables.at(x_index).lbound; x < variables.at(x_index).ubound - step; x += step)
    {
        variables.at(x_index).value = x;
        points.push_back(evaluate_point(variables));
    }
    return points;
}