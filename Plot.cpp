//
// Created by stefanciutac on 26/06/2026.
//

#include <raylib.h>
#include <cmath>

#include "Plot.h"
#include "System.h"
#include "UIElements.h"

Plot::Plot(const std::vector<Variable>& v)
    :system(v), ui_elements(v)
{
    macros.resize(v.size());
}

double Plot::minmax(double min_ideal, double max_ideal, double min_in_data, double max_in_data, double x)
{
    if (max_in_data - min_in_data == 0) return 0;
    return min_ideal + ((x - min_in_data) * (max_ideal - min_ideal)) / (max_in_data - min_in_data);
}

Point Plot::normalise_point(Point point)
{
    point.dims.at(x_index) = minmax(0, x_length, system.variables.at(x_index).lbound,
        system.variables.at(x_index).ubound, point.dims.at(x_index));
    point.dims.back() = minmax(0, y_length, system.variables.back().lbound, system.variables.back().ubound, point.dims.back());
    return point;
}

std::vector<Point> Plot::normalise_points(std::vector<Point> points)
{
    std::vector<Point> normalised_points{};
    for (int i = 0; i < points.size(); i ++) normalised_points.push_back(normalise_point(points.at(i)));
    return normalised_points;
}

Point Plot::offset_point(Point point)
{
    Point offset_point = point;
    offset_point.dims.at(x_index) += window_width / 2;
    offset_point.dims.back() += window_height / 4;
    return offset_point;
}

std::vector<Point> Plot::offset_points(std::vector<Point> points)
{
    std::vector<Point> offset_points{};
    for (Point point: points) offset_points.push_back(offset_point(point));
    return offset_points;
}

/*
std::vector<Point> Plot::manage_macros()
{
    for (int i = 0; i < system.variables.size(); i ++)
    {
        if (frame_counter > macro_duration_frames) break;  // change frame counter logic once vectors implemented
        if (macros.at(i).size())
        {
            system.variables.at(i).value = macro_duration_frames / frame_counter * system.variables.at(i).ubound;
        }
    }
}
*/

void Plot::plot_graph()
{
    // Raylib boilerplate
    InitWindow(window_width, window_height, "ParaPlot");
    SetTargetFPS(90);

    // main rendering loop
    while(!WindowShouldClose())
    {
        // evaluate function
        std::vector<Point> points_to_render{};
        std::vector<Point> points_to_normalise = system.evaluate_points(system.variables, x_index, x_step);
        std::vector<Point> normalised_points = normalise_points(points_to_normalise);
        points_to_render = normalised_points;

        // rendering logic
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // call rendering procedures here
        ui_elements.render_points(points_to_render, graph_centre, x_index, system.variables);
        ui_elements.render_axes(graph_centre, system.variables.at(x_index), system.variables.back(), x_length, y_length, window_width, window_height);

        for (int i = 0; i < system.variables.size() - 2; i ++) ui_elements.render_slider(system.variables.at(i), i);

        int x_interval = minmax(0, x_length, 0,
        (system.variables.at(x_index).ubound - system.variables.at(x_index).lbound), x_grid_interval);
        int y_interval = minmax(0, y_length, 0,
        (system.variables.back().ubound - system.variables.back().lbound), y_grid_interval);

        if (show_grid) ui_elements.render_grid(graph_centre, x_interval, y_interval, x_length, y_length);
        ui_elements.render_button(show_grid, 0, 0, window_width, "Toggle Grid");

        int title_offset = -300;
        int x_label_offset = 15;
        int y_label_offset = 30;
        ui_elements.render_labels(graph_centre, x_interval, y_interval, x_length, y_length, title_offset, x_label_offset,
            y_label_offset, "Displacement Against Time in a Simple Harmonic Oscillator", "T/s", "S/m",
            system.variables.at(x_index), system.variables.back());

        EndDrawing();
    }

    CloseWindow();
}
