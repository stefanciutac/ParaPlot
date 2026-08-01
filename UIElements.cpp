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
    int length = 150;
    int x_padding = 35;
    int text_padding = 20;
    int font_size = 20;
    int radius = 10;

    // poll
    if ((CheckCollisionPointCircle(GetMousePosition(), Vector2{float(x_padding + (variable.value - variable.lbound)
        / (variable.ubound - variable.lbound) * length), float(y)}, radius + 10) || is_moving_slider.at(number))
        && IsMouseButtonDown(0) && GetMouseX() > x_padding && GetMouseX() < x_padding + length)
    {
        variable.value = (double(GetMouseX()) - double(x_padding)) / double(length) * (variable.ubound - variable.lbound) + variable.lbound;
        is_moving_slider.at(number) = true;
    }
    if (IsMouseButtonUp(0)) is_moving_slider.at(number) = false;

    // render slider
    DrawLine(x_padding, y, x_padding + length, y, BLUE);
    DrawCircle(x_padding + (variable.value - variable.lbound) / (variable.ubound - variable.lbound) * length, y, radius, variable.colour);
    DrawText(&(variable.name + " = " + std::to_string(variable.value)).front(), x_padding + length + text_padding, y - font_size / 2, font_size, BLACK);

    // render border
    DrawRectangleLines(x_padding - 10, y - font_size / 2 - 10, length + 20, font_size + 20, BLACK);
}

void UIElements::render_axes(Point& corner, Variable x, Variable y, int& x_length, int& y_length, int window_width, int window_height)
{
    // poll graph resize: this can be simplified with some helper functions in the future
    // translate graph
    if ((CheckCollisionPointCircle(GetMousePosition(), Vector2{float(corner.dims.front()), float(corner.dims.back())}, 20)
        || is_moving_axes) && IsMouseButtonDown(0))
    {
        corner.dims = {double(std::min(window_width - x_length - 50, std::max(50, GetMouseX()))),
            double(std::min(window_height - 50, std::max(y_length + 50, GetMouseY())))};
        is_moving_axes = true;
    }
    if (IsMouseButtonUp(0)) is_moving_axes = false;

    // resize x-axis
    if ((CheckCollisionPointCircle(GetMousePosition(), Vector2{float(corner.dims.front() + x_length), float(corner.dims.back())}, 20)
        || is_changing_x) && IsMouseButtonDown(0))
    {
        x_length = std::min(window_width - 50 - int(corner.dims.front()), std::min(window_width - 100, std::max(50, GetMouseX() - int(corner.dims.front()))));
        is_changing_x = true;
    }
    if (IsMouseButtonUp(0)) is_changing_x = false;

    // resize y-axis
    if ((CheckCollisionPointCircle(GetMousePosition(), Vector2{float(corner.dims.front()), float(corner.dims.back() - y_length)}, 20)
        || is_changing_y) && IsMouseButtonDown(0))
    {
        y_length = std::min(int(corner.dims.back()) - 50, std::max(50, int(corner.dims.back()) - GetMouseY()));
        is_changing_y = true;
    }
    if (IsMouseButtonUp(0)) is_changing_y = false;

    // grab points
    if (is_moving_axes) DrawCircle(corner.dims.front(), corner.dims.back(), 10, RED);
    else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{float(corner.dims.front()), float(corner.dims.back())}, 20))
        DrawCircle(corner.dims.front(), corner.dims.back(), 10, {255, 0, 0, 192});
    else DrawCircle(corner.dims.front(), corner.dims.back(), 5, {161, 160, 161, 192});

    if (is_changing_x) DrawCircle(corner.dims.front() + x_length, corner.dims.back(), 10, RED);
    else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{float(corner.dims.front() + x_length), float(corner.dims.back())}, 20))
        DrawCircle(corner.dims.front() + x_length, corner.dims.back(), 10, {255, 0, 0, 192});
    else DrawCircle(corner.dims.front() + x_length, corner.dims.back(), 5, {161, 160, 161, 192});

    if (is_changing_y) DrawCircle(corner.dims.front(), corner.dims.back() - y_length, 10, RED);
    else if (CheckCollisionPointCircle(GetMousePosition(), Vector2{float(corner.dims.front()), float(corner.dims.back() - y_length)}, 20))
        DrawCircle(corner.dims.front(), corner.dims.back() - y_length, 10, {255, 0, 0, 192});
    else DrawCircle(corner.dims.front(), corner.dims.back() - y_length, 5, {161, 160, 161, 192});

    // axes
    Color axes_colour = {0, 0, 0, 255};
    DrawLine(std::min(window_width, std::max(0, int(corner.dims.front()))),
        std::min(window_height, std::max(0, int(corner.dims.back()))),
        std::min(window_width, std::max(0, int(corner.dims.front() + x_length))),
        std::min(window_height, std::max(0, int(corner.dims.back()))),
        axes_colour);
    DrawLine(std::min(window_width, std::max(0, int(corner.dims.front()))),
        std::min(window_height, std::max(0, int(corner.dims.back()))),
        std::min(window_width, std::max(0, int(corner.dims.front()))),
        std::min(window_height, std::max(0, int(corner.dims.back() - y_length))),
        axes_colour);

}

void UIElements::render_points(std::vector<Point> points, Point corner, int x_index, std::vector<Variable> variables)
{
    for (Point point: points) DrawCircle(corner.dims.front() + point.dims.at(x_index), corner.dims.back() - point.dims.back(), 3, variables.back().colour);
    for (int i = 1; i < points.size(); i ++) DrawLine(corner.dims.front() + points.at(i - 1).dims.at(x_index),
                                                      corner.dims.back() - points.at(i - 1).dims.back(),
                                                      corner.dims.front() + points.at(i).dims.at(x_index),
                                                      corner.dims.back() - points.at(i).dims.back(), BLACK);
}