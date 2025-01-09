#pragma once

#define START_POSITION {0, 0}

struct Position {
    int x;
    int y;

    bool operator==(const Position& other) const;
    Position getRealPosition() const;
};