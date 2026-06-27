//
// Created by stefanciutac on 26/06/2026.
//

#include <raylib.h>

#include "Plot.h"
#include "System.h"

Plot::Plot()
{
}

Point Plot::find_min_xyz(std::vector<Point> points)
{
    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return a.x < b.x;
        }
    );
    int min_x = points.front().x;

    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return a.y < b.y;
        }
    );
    int min_y = points.front().y;

    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return a.z < b.z;
        }
    );
    int min_z = points.front().z;

    return Point{double(min_x), double(min_y), double(min_z)};
}

Point Plot::find_max_xyz(std::vector<Point> points)
{
    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return abs(a.x) > abs(b.x);
        }
    );
    int max_x = points.front().x;

    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return abs(a.y) > abs(b.y);
        }
    );
    int max_y = points.front().y;

    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return abs(a.z) > abs(b.z);
        }
    );
    int max_z = points.front().z;

    return Point{double(max_x), double(max_y), double(max_z)};
}


Point Plot::normalise_point(Point given_point, Point max_in_dataset, Point max_valid)
{
    int x_norm = given_point.x * std::min(1, abs(int(max_valid.x / max_in_dataset.x)));
    // std::cout << "x_norm = " << x_norm << "\tfor max_in_dataset = " << max_in_dataset.x << "\tgiven point = " << given_point.x << std::endl;
    int y_norm = given_point.y * std::min(1, int(max_valid.y / max_in_dataset.y));
    int z_norm = given_point.z * std::min(1, int(max_valid.z / max_in_dataset.z));

    // std::cout << "point = (" << x_norm << ", " << y_norm << ")" << std::endl;
    return Point{double(x_norm), double(y_norm), double(z_norm)};
}

void Plot::plot_graph()
{
    // Raylib boilerplate
    int window_width = 1800;
    int window_height = 1000;
    int centre_x = 0;
    int centre_y = 0;
    int centre_z = window_width / 2;

    InitWindow(window_width, window_height, "ParaPlot");
    SetTargetFPS(60);

    // Declare System object
    System system;
    std::vector<Point> points = system.simulate();

    while(!WindowShouldClose())
    {
        // algorithm
        std::vector<Point> points_to_render{};
        for (Point point: points) points_to_render.push_back(normalise_point(
            point, find_max_xyz(points), Point{double(window_width), double(window_height), double(window_height)}));

        // rendering logic
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (Point point: points_to_render)
        {
            DrawCircle(centre_x + point.x - find_min_xyz(points_to_render).x, centre_y + point.y - find_min_xyz(points_to_render).y, point_radius, RED);
            std::cout << "point drawn at: x = " << centre_x + point.x - find_min_xyz(points_to_render).x << "\ty = " << centre_y + point.y - find_min_xyz(points_to_render).y << std::endl;
        }

        for (int i = 1; i < points_to_render.size(); i++) DrawLine(
            centre_x + points_to_render.at(i - 1).x - find_min_xyz(points_to_render).x,
            centre_y + points_to_render.at(i - 1).y - find_min_xyz(points_to_render).y,
            centre_x + points_to_render.at(i).x - find_min_xyz(points_to_render).x,
            centre_y + points_to_render.at(i).y - find_min_xyz(points_to_render).y, RED);

        EndDrawing();
    }

    CloseWindow();
}
