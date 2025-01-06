#include "utils/position.hpp"

bool Position::operator==(const Position& other) const {
    return this->x == other.x && this->y == other.y;
}