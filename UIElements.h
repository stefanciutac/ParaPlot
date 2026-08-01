//
// Created by s-ciutac on 29/07/2026.
//

#ifndef PARAPLOT_UIELEMENTS_H
#define PARAPLOT_UIELEMENTS_H

#include <vector>

#include "Structs.h"

class UIElements
{
private:
    std::vector<bool> is_moving_slider{};
    bool is_moving_axes = false;
    bool is_changing_x = false;
    bool is_changing_y = false;
public:
    UIElements(std::vector<Variable> v);
    void render_slider(Variable& variable, int number);
    void render_axes(Point& corner, Variable x, Variable y, int& x_length, int& y_length, int window_width, int window_height);
    void render_points(std::vector<Point> points, Point corner, int x_index, std::vector<Variable> variables);
    /*
    void render_grid(int x_interval, int y_interval);
    void render_labels(std::string title, std::string x_label, std::string y_label);
    */
};
#endif //PARAPLOT_UIELEMENTS_H
