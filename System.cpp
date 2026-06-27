//
// Created by stefanciutac on 26/06/2026.
//

#include "System.h"
#include "Constants.h"

System::System()
{
}

//
// P1 Implementation
//
Point System::angle_to_cartesian(double angle, double s)
{
    return { s * std::sin(angle), s * std::cos(angle)};
}

std::vector<Point> System::simulate()
{
    std::random_device seed;
    std::mt19937 rng_engine(seed());
    std::uniform_real_distribution<double> distribution(0.0, 2.0 * PI);

    std::vector<double> xy_angles{};
    std::vector<double> xz_angles{};

    for (int i = 0; i < N; i ++) xy_angles.push_back(distribution(rng_engine));
    for (int i = 0; i < N; i ++) xz_angles.push_back(distribution(rng_engine));

    std::vector<Point> points{};

    double net_x;
    double net_y;
    double net_z;

    for (int i = 0; i < N; i ++)
    {
        net_x += angle_to_cartesian(xy_angles.at(i), s).x;
        net_y += angle_to_cartesian(xy_angles.at(i), s).y;
        net_z += angle_to_cartesian(xz_angles.at(i), s).y;  // yes, this is meant to be y
        points.push_back(Point{ net_x, net_y, net_z});
    }

    return points;
}
//
// End of P1 Implementation
//