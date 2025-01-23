#include <cmath>

#include "utils/mathUtils.hpp"

namespace math{
    float calculateDistace(Position& p1, Position& p2){
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

    // Helper function to check if a point is inside the trapezium
    bool isPointInTrapezium(int px, int py, const Trapezium& trapz) {
        SDL_Point p = {px, py};
        Triangle tri1 = {{trapz.top_left.x, trapz.top_left.y},
                        {trapz.top_right.x, trapz.top_right.y},
                        {trapz.bottom_left.x, trapz.bottom_left.y}
                        };
        Triangle tri2 = {{trapz.top_right.x, trapz.top_right.y},
                        {trapz.bottom_right.x, trapz.bottom_right.y},
                        {trapz.bottom_left.x, trapz.bottom_left.y}
                        };
        return isPointInTriangle(p, tri1) || isPointInTriangle(p, tri2);
    }

    bool isPointInTriangle(SDL_Point p, Triangle& tri) {
        int px = p.x;
        int py = p.y;

        // Calculate the barycentric coordinates of the point relative to the triangle
        int d1 = (px - tri.v2.x) * (tri.v1.y - tri.v2.y) - (tri.v1.x - tri.v2.x) * (py - tri.v2.y);
        int d2 = (px - tri.v3.x) * (tri.v2.y - tri.v3.y) - (tri.v2.x - tri.v3.x) * (py - tri.v3.y);
        int d3 = (px - tri.v1.x) * (tri.v3.y - tri.v1.y) - (tri.v3.x - tri.v1.x) * (py - tri.v1.y);

        // Determine if the point lies within the triangle
        int has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        int has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }

}