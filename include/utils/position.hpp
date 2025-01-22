#pragma once

#include "pch.h"

/// @brief Defines the default start position as {0, 0} from the top left corner.
#define START_POSITION {0, 0}

/// @brief Represents a 2D position with x and y coordinates.
/// 
/// This struct provides utility functions for comparing positions
/// and converting them to SDL's `SDL_Point` structure.
struct Position {
    int x; ///< The x-coordinate of the position.
    int y; ///< The y-coordinate of the position.

    /// @brief Compares two positions for equality.
    /// @param other The position to compare against.
    /// @return `true` if both x and y coordinates are equal, otherwise `false`.
    bool operator==(const Position& other) const;

    /// @brief Converts the position to an SDL-compatible `SDL_Point` structure.
    /// 
    /// This function is useful when working with SDL rendering functions
    /// that require positions in the `SDL_Point` format.
    /// 
    /// @return An `SDL_Point` with the same x and y coordinates.
    SDL_Point getRealPosition() const;
};
