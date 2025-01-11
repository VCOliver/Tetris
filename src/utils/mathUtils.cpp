#include <cmath>

#include "utils/mathUtils.hpp"

namespace math{
    float calculateDistace(Position& p1, Position& p2){
        return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
    }

}