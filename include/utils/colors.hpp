#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

typedef std::uint8_t rgba_t;

/**
 * @struct Color
 * @brief Represents an RGB color.
 */
struct Color {
    rgba_t red; ///< Red component of the color.
    rgba_t green; ///< Green component of the color.
    rgba_t blue; ///< Blue component of the color.

    /**
     * @brief Constructs a Color with the specified red, green, and blue components.
     * 
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    constexpr Color(rgba_t r, rgba_t g, rgba_t b) : red(r), green(g), blue(b) {}

    SDL_Color toSDL_Color();
};

/**
 * @namespace Colors
 * @brief Contains predefined colors.
 */
namespace Colors {
    constexpr Color RED(255, 0, 0); ///< Predefined red color.
    constexpr Color GREEN(0, 255, 0); ///< Predefined green color.
    constexpr Color BLUE(0, 0, 255); ///< Predefined blue color.
    constexpr Color WHITE(255, 255, 255); ///< Predefined white color.
    constexpr Color BLACK(0, 0, 0); ///< Predefined black color.
    constexpr Color CYAN(0, 255, 255); ///< Predefined cyan color.
    constexpr Color YELLOW(255, 255, 0); ///< Predefined yellow color.
    constexpr Color PURPLE(128, 0, 128); ///< Predefined purple color.
    constexpr Color ORANGE(255, 165, 0); ///< Predefined orange color.
    constexpr Color GRAY(128, 128, 128);
}