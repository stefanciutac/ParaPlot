//
// Created by stefanciutac on 26/06/2026.
//

#include "System.h"

System::System(const std::vector<Variable>& v, int i, double s)
    :variables(v), x_index(i), step(s)
{
}

Point System::evaluate_point()
{
    // your code goes here
    // example: oscillator
    double amplitude = variables.at(0).value;
    double frequency = variables.at(1).value;
    double phase = variables.at(2).value;
    double time = variables.at(3).value;

    double position = amplitude * std::cos(frequency * time + phase);
    variables.back().value = position;

    return Point{{amplitude, frequency, phase, time, position}};
}

std::vector<Point> System::evaluate_points()
{
    std::vector<Point> points;

    for (double x = variables.at(x_index).lbound; x < variables.at(x_index).ubound - step; x += step)
    {
        variables.at(x_index).value = x;
        points.push_back(evaluate_point());
    }
    return points;
}