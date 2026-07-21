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

/*
Point Plot::transform_point(Point point, Point centre, double rotation_xy, double rotation_xz, double rotation_zy)
{
    // calculate distance between point and centre of rotation in each plane
    double radius_xz = std::sqrt(std::pow(centre.x - point.x, 2) + std::pow(centre.z - point.z, 2));
    double radius_zy = std::sqrt(std::pow(centre.z - point.z, 2) + std::pow(centre.y - point.y, 2));
    double radius_xy = std::sqrt(std::pow(centre.x - point.x, 2) + std::pow(centre.y - point.y, 2));

    // PI / 2.0 term added to fix mysterious offset otherwise
    double original_angle_xy = std::acos((double(point.x) - double(centre.x)) / std::max(radius_xy, 0.000000000000001)) + PI / 2.0;
    double original_angle_xz = std::acos((double(point.x) - double(centre.x)) / std::max(radius_xz, 0.000000000000001)) + PI / 2.0;
    double original_angle_zy = std::acos((double(point.z) - double(centre.z)) / std::max(radius_zy, 0.000000000000001)) + PI / 2.0;

    // work out new coordinates
    double x_new = centre.x + (radius_xy * std::cos(original_angle_xy + rotation_xy)) + (radius_xz * std::cos(original_angle_xz + rotation_xz));
    double y_new = centre.y + (radius_xy * std::sin(original_angle_xy + rotation_xy)) + (radius_zy * std::sin(original_angle_zy + rotation_zy));
    double z_new = centre.z + (radius_xz * std::sin(original_angle_xz + rotation_xz)) + (radius_zy * std::cos(original_angle_zy + rotation_zy));

    std::cout << "x, y, z = " << x_new << ", " << y_new << ", " << z_new << std::endl;
    return Point{x_new, y_new, z_new};
}
*/

std::vector<double> Plot::rotate_coords(double x, double y, double angle)  // matrix approach to new angles, returns {x, y}
{
    return {x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle)};
}

Point Plot::rotate_point(Point point, std::vector<double> rotations_vector)  // {xy, xz, zy}
{
    double x_new = point.x - centre.x;
    double y_new = point.y - centre.y;
    double z_new = point.z - centre.z;

    x_new = rotate_coords(x_new, y_new, rotations_vector.at(0)).at(0);
    y_new = rotate_coords(x_new, y_new, rotations_vector.at(0)).at(1);

    x_new = rotate_coords(x_new, z_new, rotations_vector.at(1)).at(0);
    z_new = rotate_coords(x_new, z_new, rotations_vector.at(1)).at(1);

    z_new = rotate_coords(z_new, y_new, rotations_vector.at(2)).at(0);
    y_new = rotate_coords(z_new, y_new, rotations_vector.at(2)).at(1);

    return Point{x_new + centre.x, y_new + centre.y, z_new + centre.z};
}

std::vector<Point> Plot::transform_points(std::vector<Point> points, std::vector<double> rotations_vector)
{
    std::vector<Point> new_points{};
    for (Point point: points) new_points.push_back(rotate_point(point, rotations_vector));

    return new_points;
}

void Plot::plot_graph()
{
    // Raylib boilerplate

    InitWindow(window_width, window_height, "ParaPlot");
    SetTargetFPS(60);

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


        points_to_render = transform_points(points_to_render, {0.0, 0.0, 0.2});


        Point min_point = find_min_xyz(points_to_render);
        Point max_point = find_max_xyz(points_to_render);
        //for (Point& point: points_to_render) point = normalise_point(min_point, max_point, point);


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
