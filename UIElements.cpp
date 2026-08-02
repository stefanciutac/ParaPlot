//
// Created by s-ciutac on 29/07/2026.
//

#include "UIElements.h"

#include <raylib.h>
#include <iostream>
#include <cmath>

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

void UIElements::render_button(bool& show_grid, int number_vertical, int number_horizontal, int window_width, std::string text)
{
    int x_padding = 35;
    int y_padding = 30;
    float button_height = 40;
    float button_width = 145;
    float button_x = window_width - button_width - x_padding - (number_horizontal * (button_width + 10));;
    float button_y = number_vertical * 50 + y_padding;

    int font_size = 20;

    Rectangle button = {button_x, button_y, button_width, button_height};
    bool is_hovering = CheckCollisionPointRec(GetMousePosition(), button);
    bool has_clicked = IsMouseButtonPressed(0);

    Color default_colour = {161, 160, 161, 192};
    Color hover_colour = {255, 0, 0, 192};
    Color clicked_colour = RED;

    if (is_hovering && has_clicked)
    {
        DrawRectangleRec(button, clicked_colour);
        if (show_grid) show_grid = false;
        else show_grid = true;
    }
    else if (is_hovering) DrawRectangleRec(button, hover_colour);
    else DrawRectangleRec(button, default_colour);

    float text_x_offset = 10;
    float text_y_offset = 10;

    DrawText(&text.front(), button_x + text_x_offset, button_y + text_y_offset, font_size, BLACK);
}

void UIElements::render_grid(Point corner, int x_interval, int y_interval, int x_length, int y_length)
{
    int cx = corner.dims.front();
    int cy = corner.dims.back();

    Color grid_colour = {113, 111, 113, 192};

    for (int i = 0; i <= x_length; i += x_interval) DrawLine(cx + i, cy, cx + i, cy - y_length, grid_colour);
    for (int i = 0; i <= y_length; i += y_interval) DrawLine(cx, cy - i, cx + x_length, cy - i, grid_colour);
}

std::string UIElements::round(int no_of_dp, float x)
{
    std::string var = std::to_string(x);
    std::string rounded_x{};

    bool point_reached = false;
    int decimal_counter{};

    for (char letter: var)
    {
        if (letter != '.' && !point_reached) rounded_x += letter;
        else if (letter != '.' && point_reached && decimal_counter < no_of_dp)
        {
            rounded_x += letter;
            decimal_counter ++;
        }
        else if (letter == '.')
        {
            rounded_x += letter;
            point_reached = true;
        }
    }
    return rounded_x;
}

void UIElements::render_labels(Point corner, int x_interval, int y_interval, int x_length, int y_length, int title_offset,
    int x_label_offset, int y_label_offset, std::string title, std::string x_label, std::string y_label, Variable x, Variable y)
{
    int cx = corner.dims.front();
    int cy = corner.dims.back();

    int nums_x_offset = -5;
    int nums_y_offset = 5;
    Vector2 title_xy = {float(x_length / 2 + cx + title_offset), float(cy - y_length - 40)};
    Vector2 x_label_xy = {float(x_length / 2 + cx + x_label_offset), float(cy + 30)};
    Vector2 y_label_xy = {float(cx - 30 - y_label_offset), float(cy - y_length / 2)};

    // render graph and axis titles
    DrawText(&title.front(), title_xy.x, title_xy.y, 20, BLACK);
    DrawText(&x_label.front(), x_label_xy.x, x_label_xy.y, 15, BLACK);
    DrawText(&y_label.front(), y_label_xy.x, y_label_xy.y, 15, BLACK);

    int x_tick_length = x_length / 140;
    int y_tick_length = y_length / 140;

    // render ticks
    for (int i = 0; i <= x_length; i += x_interval) DrawLine(cx + i, cy + x_tick_length, cx + i, cy - x_tick_length, BLACK);
    for (int i = 0; i <= y_length; i += y_interval) DrawLine(cx - y_tick_length, cy - i, cx + y_tick_length, cy - i, BLACK);

    // render scale
    for (int i = 0; i <= x_length; i += x_interval)
    {
        std::string x_text = round(1, (x.ubound - x.lbound) * (float(i) / float(x_length)) + x.lbound);
        DrawText(&x_text.front(), cx + i, cy + 15, 10, BLACK);
    }
    for (int i = 0; i <= y_length; i += y_interval)
    {
        std::string y_text = round(1, (y.ubound - y.lbound) * (float(i) / float(y_length)) + y.lbound);
        DrawText(&y_text.front(), cx - 25, cy - i, 10, BLACK);
    }
}

void UIElements::render_points(std::vector<Point> points, Point corner, int x_index, std::vector<Variable> variables)
{
    for (Point point: points) DrawCircle(corner.dims.front() + point.dims.at(x_index), corner.dims.back() - point.dims.back(), 3, variables.back().colour);
    for (int i = 1; i < points.size(); i ++) DrawLine(corner.dims.front() + points.at(i - 1).dims.at(x_index),
                                                      corner.dims.back() - points.at(i - 1).dims.back(),
                                                      corner.dims.front() + points.at(i).dims.at(x_index),
                                                      corner.dims.back() - points.at(i).dims.back(), BLACK);
}