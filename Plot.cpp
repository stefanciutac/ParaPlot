//
// Created by stefanciutac on 26/06/2026.
//

#include <raylib.h>
#include <cmath>

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
    if (max_data - min_data == 0) return 0;
    return min_target + ((x - min_data) * (max_target - min_target)) / (max_data - min_data);
}

Point Plot::normalise_point(Point min_data, Point max_data, Point point)
{
    return Point{
        double(minmax(100, window_width - 100, min_data.x, max_data.x, point.x)),
        double(minmax(100, window_height - 100, min_data.y, max_data.y, point.y)),
        double(minmax(100, window_depth - 100, min_data.z, max_data.z, point.z))};
}

Point Plot::transform_point(Point point, Point centre, double rotation_xy, double rotation_xz, double rotation_zy)
{
    // calculate original angles
    double original_angle_xz = std::atan(std::abs(centre.x - point.x) / std::max(std::abs(centre.z - point.z), 0.0001));

    std::cout << "numerator: = " << std::abs(centre.x - point.x) << "\tdenominator = " << std::max(std::abs(centre.z - point.z), 0.0001) << std::endl;

    std::cout << point.x << "\t" << point.y << "\t" << point.z << "\toriginal_angle_xz = " << original_angle_xz << std::endl;
    double original_angle_zy = std::atan(std::abs(centre.z - point.z) / std::max(std::abs(centre.y - point.y), 0.0001));
    std::cout << point.x << "\t" << point.y << "\t" << point.z << "\toriginal_angle_zy = " << original_angle_zy << std::endl;
    double original_angle_xy = std::atan(std::abs(centre.x - point.x) / std::max(std::abs(centre.y - point.y), 0.0001));
    std::cout << point.x << "\t" << point.y << "\t" << point.z << "\toriginal_angle_xy = " << original_angle_xy << std::endl;

    // calculate distance between point and centre of rotation in each plane
    double dist_xz = std::sqrt(std::pow(centre.x - point.x, 2) + std::pow(centre.z - point.z, 2));
    double dist_zy = std::sqrt(std::pow(centre.z - point.z, 2) + std::pow(centre.y - point.y, 2));
    double dist_xy = std::sqrt(std::pow(centre.x - point.x, 2) + std::pow(centre.y - point.y, 2));

    // work out new coordinates
    double x_new = centre.x + (dist_xy * std::sin(original_angle_xy)) + (dist_xz * std::sin(original_angle_xz));
    double y_new = centre.y + (dist_xy * std::cos(original_angle_xy)) + (dist_zy * std::cos(original_angle_zy));
    double z_new = centre.z + (dist_xz * std::cos(original_angle_xz)) + (dist_zy * std::sin(original_angle_zy));

    return Point{x_new, y_new, z_new};
}

std::vector<Point> Plot::transform_points(std::vector<Point> points, Point centre, double rotation_xy, double rotation_xz, double rotation_zy)
{
    std::vector<Point> new_points{};
    for (Point point: points) new_points.push_back(transform_point(point, centre, rotation_xy, rotation_xz, rotation_zy));

    return new_points;
}

void Plot::plot_graph()
{
    // Raylib boilerplate

    InitWindow(window_width, window_height, "ParaPlot");
    SetTargetFPS(1);

    // Declare System object
    System system;
    std::vector<Point> points = system.simulate();

    std::vector<Point> points_to_render{};

    while(!WindowShouldClose())
    {
        // algorithm
        if (conditions_changed)
        {
            for (Point point: points) points_to_render.push_back(normalise_point(find_min_xyz(points), find_max_xyz(points), point));
        }

        conditions_changed = false;


        points_to_render = transform_points(points_to_render, Point{
                                                double(window_width) / 2.0, double(window_height) / 2.0,
                                                double(window_depth) / 2.0},
                                                0.0, 0.0, 0.0);

        Point min_point = find_min_xyz(points_to_render);
        Point max_point = find_max_xyz(points_to_render);
        for (Point& point: points_to_render) point = normalise_point(min_point, max_point, point);


        // rendering logic
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (Point point: points_to_render)
        {
            DrawCircle(point.x, window_height - point.y, point_radius, RED);
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
