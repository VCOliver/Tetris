#pragma once

#include <stdexcept> // For exception handling 

struct Color
{
    int red;
    int green;
    int blue;

    constexpr Color(int r, int g, int b) : red(r), green(g), blue(b) {
        if (!isValidValue(r) || !isValidValue(g) || !isValidValue(b)) {
            throw std::invalid_argument("RGB values should be between 0 and 255");
        }
    }

private:
    constexpr bool isValidValue(int value) const {
        return (value <= 255 && value >= 0);
    }
};

namespace Colors
{
    constexpr Color RED(255, 0, 0);
    constexpr Color GREEN(0, 255, 0);
    constexpr Color BLUE(0, 0, 255);
    constexpr Color WHITE(255, 255, 255);
    constexpr Color BLACK(0, 0, 0);
    constexpr Color CYAN(0, 255, 255);
    constexpr Color YELLOW(255, 255, 0);
    constexpr Color PURPLE(128, 0, 128);
    constexpr Color ORANGE(255, 165, 0);
}