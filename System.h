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
    //
    // P1 Declaration
    //

    // parameters
    int N = 1000;  // number of steps
    double s = 1.0; // step size

    Point angle_to_cartesian(double angle, double s);

    //
    // End of P1 declaration
    //
public:
    System();

    std::vector<Point> simulate();
};


#endif //PARAPLOT_SYSTEM_H
