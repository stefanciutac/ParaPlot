//
// Created by stefanciutac on 26/06/2026.
//

#ifndef PARAPLOT_PLOT_H
#define PARAPLOT_PLOT_H

#include <vector>

#include "Structs.h"
#include "System.h"
#include "UIElements.h"

class Plot {
private:
    // window variables
    int window_width;
    int window_height;
    int fps;

    // graph variables
    Point graph_corner = Point{{100, double(window_height) - 100}};
    int x_length = window_width - 300;
    int y_length = window_height / 2;
    int x_index;
    int x_padding = 25;
    double x_step;
    bool show_grid = true;
    double x_grid_interval;
    double y_grid_interval;


    // classes
    System system;
    UIElements ui_elements;

    // macro variables
    std::vector<std::vector<double>> macros{};
    std::vector<bool> recording_macro{};
    std::vector<bool> playing_macro{};
    std::vector<bool> is_empty_macro{};
    std::vector<int> frame_counters{};

    // methods
    double minmax(double min_target, double max_ideal, double min_in_data, double max_in_data, double x);
    Point normalise_point(Point point);
    std::vector<Point> normalise_points(std::vector<Point> points);
    Point offset_point(Point point);
    std::vector<Point> offset_points(std::vector<Point> points);
    void manage_macros();
    void poll_macro_buttons();

public:
    Plot(const std::vector<Variable>& variables, int x_index, double step, int window_width, int window_height, int fps,
         double x_grid_interval, double y_grid_interval);
    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
