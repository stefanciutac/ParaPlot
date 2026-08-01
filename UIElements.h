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
public:
    UIElements(std::vector<Variable> v);
    void render_slider(Variable& variable, int number);
    void render_axes(Point centre, Variable x, Variable y, int x_length, int y_length, int& pos_x_length, int& pos_y_length,
                     int& neg_x_length, int& neg_y_length, int x_padding);
    void render_points(std::vector<Point> points, int x_index, int window_height, int x_padding);
    /*
    void render_grid(int x_interval, int y_interval);
    void render_labels(std::string title, std::string x_label, std::string y_label);
    */
};
#endif //PARAPLOT_UIELEMENTS_H
