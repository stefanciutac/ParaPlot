//
// Created by stefanciutac on 26/06/2026.
//

#ifndef PARAPLOT_PLOT_H
#define PARAPLOT_PLOT_H

#include <format>
#include <vector>
#include <raylib.h>

#include "Structs.h"

class Plot
{
private:
    int point_radius = 1;
    Point find_max_xyz(std::vector<Point> points);
    Point find_min_xyz(std::vector<Point> points);
    Point normalise_point(Point input_point, Point max_in_dataset, Point max_point);

public:
    Plot();

    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
