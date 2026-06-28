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
            return a.x > b.x;
        }
    );
    int max_x = points.front().x;

    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return a.y > b.y;
        }
    );
    int max_y = points.front().y;

    std::sort(points.begin(), points.end(),
        [](Point& a, Point& b)
        {
            return a.z > b.z;
        }
    );
    int max_z = points.front().z;

    return Point{double(max_x), double(max_y), double(max_z)};
}

double Plot::minmax(double min_target, double max_target, double min_data, double max_data, double x)
{
    return min_target + ((x - min_data) * (max_target - min_target)) / (max_data - min_data);
}

Point Plot::normalise_point(Point min_data, Point max_data, Point point)
{
    return Point{
        double(minmax(100, window_width - 100, min_data.x, max_data.x, point.x)),
        double(minmax(100, window_height - 100, min_data.y, max_data.y, point.y)),
        double(minmax(100, window_depth - 100, min_data.z, max_data.z, point.z))};
}

void Plot::plot_graph()
{
    // Raylib boilerplate

    InitWindow(window_width, window_height, "ParaPlot");
    SetTargetFPS(60);

    // Declare System object
    System system;
    std::vector<Point> points = system.simulate();

    while(!WindowShouldClose())
    {
        // algorithm
        std::vector<Point> points_to_render{};
        for (Point point: points) points_to_render.push_back(normalise_point(find_min_xyz(points), find_max_xyz(points), point));

        // rendering logic
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (Point point: points_to_render)
        {
            DrawCircle(point.x, window_height - point.y, point_radius, RED);
            std::cout << "point drawn at: x = " << centre_x + point.x - find_min_xyz(points_to_render).x << "\ty = " << centre_y + point.y - find_min_xyz(points_to_render).y << std::endl;
        }

        for (int i = 1; i < points_to_render.size(); i++) DrawLine(
            points_to_render.at(i - 1).x,
            window_height - points_to_render.at(i - 1).y,
            points_to_render.at(i).x,
            window_height - points_to_render.at(i).y, RED);

        EndDrawing();
    }

    CloseWindow();
}
