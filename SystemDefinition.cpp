//
// Created by s-ciutac on 29/07/2026.
//

#include <iostream>
#include <vector>
#include <cmath>

#include "Structs.h"

// user-defined function
Point evaluate_point(std::vector<Variable>& variables)
{
    // example: oscillator
    double amplitude = variables.at(0).value;
    double frequency = variables.at(1).value;
    double phase = variables.at(2).value;
    double time = variables.at(3).value;

    double position = amplitude * std::cos(frequency * time + phase);
    variables.back().value = position;

    return Point{{amplitude, frequency, phase, time, position}};
}
