#include <iostream>

#include "Plot.h"
#include "Structs.h"

int main()
{
    const double PI = 3.14;
    double amplitude = 5.0;
    Plot plot({Variable{0.5, 0.0, amplitude, "amplitude"},
                          Variable{3.0, 0.1, 10.0, "frequency"},
                          Variable{-PI / 2, -PI / 2, PI / 2, "phase"},
                          Variable{0.0, 0.0, 6.0, "time"},
                          Variable{0, -amplitude, amplitude, "position"}});
    plot.plot_graph();
}