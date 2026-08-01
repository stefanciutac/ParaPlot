//
// Created by stefanciutac on 26/06/2026.
//

#ifndef PARAPLOT_PLOT_H
#define PARAPLOT_PLOT_H

#include <vector>

#include "Structs.h"
#include "System.h"

class Plot
{
private:
    // graph variables
    int point_radius = 30;
    Point graph_centre = Point{{500, 500}};
    int x_length = 500;
    int y_length = 500;
    int x_index = 3;

    int pos_x_length;
    int pos_y_length;
    int neg_x_length;
    int neg_y_length;

    int x_padding = 50;

    double x_step = 0.001;

    // window variables
    int window_width = 1000;
    int window_height = 1000;

    double minmax(double min_target, double max_ideal, double min_in_data, double max_in_data, double x);
    Point normalise_point(Point point);
    std::vector<Point> normalise_points(std::vector<Point> points);
    Point offset_point(Point point);
    std::vector<Point> offset_points(std::vector<Point> points);

    System system;

public:
    Plot(const std::vector<Variable>& variables);
    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
