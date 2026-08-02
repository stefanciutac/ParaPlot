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
    int window_width = 1000;
    int window_height = 1000;
    const int fps = 60;

    // graph variables
    int point_radius = 30;
    Point graph_centre = Point{{100, double(window_height) - 100}};
    int x_length = window_width - 300;
    int y_length = window_height / 2;
    int x_index = 3;
    int x_padding = 25;
    double x_step = 0.001;
    bool show_grid = true;
    double x_grid_interval = 1.0;
    double y_grid_interval = 1.0;


    // classes
    System system;
    UIElements ui_elements;

    // macro variables
    int frame_counter{};
    std::vector<std::vector<double>> macros{};
    std::vector<bool> is_recording_macro;
    double macro_duration_seconds = 5.0;
    int macro_duration_frames = fps * macro_duration_seconds;

    // methods
    double minmax(double min_target, double max_ideal, double min_in_data, double max_in_data, double x);
    Point normalise_point(Point point);
    std::vector<Point> normalise_points(std::vector<Point> points);
    Point offset_point(Point point);
    std::vector<Point> offset_points(std::vector<Point> points);

public:
    Plot(const std::vector<Variable>& variables);
    void plot_graph();
};


#endif //PARAPLOT_PLOT_H
