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
    void render_grid(Point corner, int x_interval, int y_interval, int x_length, int y_length);
    void render_button(bool& variable, int number_vertical, int number_horizontal, int window_width, std::string text);
    void render_labels(Point corner, int x_interval, int y_interval, int x_length, int y_length, int title_offset, int x_label_offset,
        int y_label_offset, std::string title, std::string x_label, std::string y_label, Variable x, Variable y);

    std::string truncate(int no_of_dp, float x);
};
#endif //PARAPLOT_UIELEMENTS_H
