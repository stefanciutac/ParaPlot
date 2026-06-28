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
    int point_radius = 3;
    Point find_max_xyz(std::vector<Point> points);
    Point find_min_xyz(std::vector<Point> points);
    Point normalise_point(Point input_point, Point max_in_dataset, Point max_point);
    double minmax(double min_target, double max_target, double min_data, double max_data, double x);

    int window_width = 1800;
    int window_height = 1000;
    int window_depth = 1800;
    int centre_x = 0;
    int centre_y = 0;
    int centre_z = window_width / 2;

public:
    Plot();

    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
