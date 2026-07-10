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
    int point_radius = 30;
    Point find_max_xyz(std::vector<Point> points);
    Point find_min_xyz(std::vector<Point> points);
    Point normalise_point(Point input_point, Point max_in_dataset, Point max_point);
    double minmax(double min_target, double max_target, double min_data, double max_data, double x);

    int window_width = 1000;
    int window_height = 1000;
    int window_depth = 1000;
    int centre_x = 0;
    int centre_y = 0;
    int centre_z = 0;

    bool conditions_changed = true;

    Point transform_point(Point point, Point centre, double rotation_xy, double rotation_xz, double rotation_zy);
    std::vector<Point> transform_points(std::vector<Point> points, Point centre, double rotation_xy, double rotation_xz, double rotation_zy);

public:
    Plot();

    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
