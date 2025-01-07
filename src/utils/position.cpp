#include "utils/position.hpp"

bool Position::operator==(const Position& other) const {
    return this->x == other.x && this->y == other.y;
}

Position Position::getRealPosition() const {
    return {this->x*20, this->y*20};
}