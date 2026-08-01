//
// Created by s-ciutac on 29/07/2026.
//

#ifndef PARAPLOT_UIELEMENTS_H
#define PARAPLOT_UIELEMENTS_H

#include <vector>

#include "Structs.h"

void render_slider(Variable variable, int number);
void render_axes(Point centre, Variable x, Variable y, int x_length, int y_length, int& pos_x_length, int& pos_y_length,
                 int& neg_x_length, int& neg_y_length, int x_padding);
void render_points(std::vector<Point> points, int x_index, int window_height, int x_padding);

#endif //PARAPLOT_UIELEMENTS_H
