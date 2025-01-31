#include "utils/position.hpp"
#include "core/base.hpp"

bool Position::operator==(const Position& other) const {
    return this->x == other.x && this->y == other.y;
}

Position Position::operator+(const Position& other) const {
    return {this->x + other.x, this->y + other.y};
}

SDL_Point Position::getRealPosition() const {
    return {this->x*STD_BLOCK_W, this->y*STD_BLOCK_H};
}