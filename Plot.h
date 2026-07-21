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
    Point centre{500, 500, 500};

    bool conditions_changed = true;

    std::vector<double> rotate_coords(double x, double y, double angle);
    Point rotate_point(Point input_point, std::vector<double> rotations);
    std::vector<Point> transform_points(std::vector<Point> points, std::vector<double> rotations_vector);

public:
    Plot();

    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
