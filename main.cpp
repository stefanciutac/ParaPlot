#include <iostream>

#include "Plot.h"
#include "Structs.h"

int main()
{
    const double pi = 3.14;
    double amplitude = 5.0;
    Plot plot({Variable{0.5, 0.0, amplitude, "amplitude", GRAY},
                          Variable{3.0, 0.1, 10.0, "frequency", BLUE},
                          Variable{-pi / 2, -pi / 2, pi / 2, "phase", DARKBLUE},
                          Variable{0.0, 0.0, 6.0, "time", PURPLE},
                          Variable{0,   -amplitude, amplitude, "position", RED}},
                          3,
                          0.001,
                          1000,
                          1000,
                          60,
                          1.0,
                          1.0);
    plot.plot_graph();
}