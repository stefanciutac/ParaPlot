//
// Created by s-ciutac on 29/07/2026.
//

#include "UIElements.h"

#include <raylib.h>
#include <iostream>

UIElements::UIElements(std::vector<Variable> v)
{
    is_moving_slider.resize(v.size());
}

void UIElements::render_slider(Variable& variable, int number) {
    int y = number * 50 + 50;
    int length = 200;
    int x_padding = 50;
    int text_padding = 20;
    int font_size = 20;
    int radius = 10;

    // poll
    if ((CheckCollisionPointCircle(GetMousePosition(), Vector2{float(x_padding + (variable.value - variable.lbound)
        / (variable.ubound - variable.lbound) * length), float(y)}, radius) || is_moving_slider.at(number))
        && IsMouseButtonDown(0) && GetMouseX() > x_padding && GetMouseX() < x_padding + length)
    {
        variable.value = (double(GetMouseX()) - double(x_padding)) / double(length) * (variable.ubound - variable.lbound) + variable.lbound;
        is_moving_slider.at(number) = true;
    }
    if (IsMouseButtonUp(0)) is_moving_slider.at(number) = false;

    // render
    DrawLine(x_padding, y, x_padding + length, y, BLUE);
    DrawCircle(x_padding + (variable.value - variable.lbound) / (variable.ubound - variable.lbound) * length, y, radius, RED);
    DrawText(&variable.name.front(), x_padding + length + text_padding, y - font_size / 2, font_size, BLACK);
    
}

void UIElements::render_axes(Point centre, Variable x, Variable y, int x_length, int y_length, int& pos_x_length, int& pos_y_length,
                 int& neg_x_length, int& neg_y_length, int x_padding)
{
    pos_x_length = std::min(x.ubound, x.ubound-x.lbound) / (x.ubound-x.lbound) * x_length;
    pos_y_length = std::min(y.ubound, y.ubound - y.lbound) / (y.ubound - y.lbound) * y_length;
    neg_x_length = x_length - pos_x_length;
    neg_y_length = y_length - pos_y_length;

    // graph lines
    DrawLine(centre.dims.at(0) - x_padding, centre.dims.at(1), centre.dims.at(0) + pos_x_length - x_padding, centre.dims.at(1), BLACK);
    DrawLine(centre.dims.at(0) - x_padding, centre.dims.at(1), centre.dims.at(0) - neg_x_length - x_padding, centre.dims.at(1), BLACK);
    DrawLine(centre.dims.at(0) - x_padding, centre.dims.at(1), centre.dims.at(0) - x_padding, centre.dims.at(1) + pos_y_length, BLACK);
    DrawLine(centre.dims.at(0) - x_padding, centre.dims.at(1), centre.dims.at(0) - x_padding, centre.dims.at(1) - neg_y_length, BLACK);
}

void UIElements::render_points(std::vector<Point> points, int x_index, int window_height, int x_padding)
{
    for (Point point: points) DrawCircle(point.dims.at(x_index) - x_padding, window_height - point.dims.back(), 3, RED);
    for (int i = 1; i < points.size(); i ++) DrawLine(points.at(i - 1).dims.at(x_index) - x_padding,
                                                      window_height - points.at(i - 1).dims.back(),
                                                      points.at(i).dims.at(x_index) - x_padding,
                                                      window_height - points.at(i).dims.back(), BLACK);
}