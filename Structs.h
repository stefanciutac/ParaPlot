//
// Created by stefanciutac on 26/06/2026.
//

#ifndef PARAPLOT_STRUCTS_H
#define PARAPLOT_STRUCTS_H

#include <raylib.h>
#include <string>

struct Point
{
    std::vector<double> dims;  // dimensions
};

struct Variable
{
    double value;
    double lbound;  // inclusive
    double ubound;  // exclusive
    std::string name;
    Color colour;
};

#endif //PARAPLOT_STRUCTS_H
