#pragma once

#include "pch.h"
#include <initializer_list>

#include "position.hpp"

namespace math {

    /**
     * @struct Triangle
     * @brief Represents a triangle using three SDL_Point vertices.
     */
    struct Triangle {
        SDL_Point v1; ///< Vertex 1 of the triangle
        SDL_Point v2; ///< Vertex 2 of the triangle
        SDL_Point v3; ///< Vertex 3 of the triangle
    };

    /**
     * @struct Trapezium
     * @brief Represents a trapezium shape with four positions.
     */
    struct Trapezium {
        SDL_Point top_left; ///< Top-left position of the trapezium.
        SDL_Point top_right; ///< Top-right position of the trapezium.
        SDL_Point bottom_left; ///< Bottom-left position of the trapezium.
        SDL_Point bottom_right; ///< Bottom-right position of the trapezium.

        Trapezium() = default;
    };

    /// @brief Calculates the distance between 2 points
    /// @param p1 Point 1
    /// @param p2 Point 2
    /// @return The distance from one point to the other
    /// @note Not being used
    float calculateDistace(Position& p1, Position& p2);

    bool isPointInTrapezium(SDL_Point& p, const Trapezium& trapz);

    bool isPointInTriangle(SDL_Point& p, Triangle& tri);

    template <typename T, size_t Rows, size_t Cols>
    struct Matrix {
        using matrix_t = std::array<std::array<T, Cols>, Rows>;
        matrix_t data;

        // Default constructor
        Matrix() = default;

        // Constructor with initializer list for easier initialization
        Matrix(const std::initializer_list<std::initializer_list<T>>& values) {
            size_t row = 0;
            for (const auto& valueRow : values) {
                size_t col = 0;
                for (const auto& value : valueRow) {
                    if (row < Rows && col < Cols) {
                        data[row][col] = value;
                        col++;
                    }
                }
                row++;
            }
        }

        // Overload () for multi-dimensional access
        T& operator()(size_t col, size_t row) {
            return data[row][col];
        }

        const T& operator()(size_t col, size_t row) const {
            return data[row][col];
        }

        // Add begin() and end() for range-based for loops
        typename matrix_t::iterator begin() {
            return data.begin();
        }

        typename matrix_t::iterator end() {
            return data.end();
        }

        typename matrix_t::const_iterator begin() const {
            return data.begin();
        }

        typename matrix_t::const_iterator end() const {
            return data.end();
        }
    };

} // namespace math

