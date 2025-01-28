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

        Matrix rotateClockwise() const {
            static_assert(Rows == Cols, "In-place rotation requires a square matrix.");
            Matrix result = *this;
            for (size_t layer = 0; layer < Rows / 2; ++layer) {
            size_t first = layer;
            size_t last = Rows - 1 - layer;
            for (size_t i = first; i < last; ++i) {
                size_t offset = i - first;
                T top = result.data[first][i];

                // Left -> Top
                result.data[first][i] = result.data[last - offset][first];

                // Bottom -> Left
                result.data[last - offset][first] = result.data[last][last - offset];

                // Right -> Bottom
                result.data[last][last - offset] = result.data[i][last];

                // Top -> Right
                result.data[i][last] = top;
            }
            }
            return result;
        }

        Matrix rotateCounterclockwise() const {
            static_assert(Rows == Cols, "In-place rotation requires a square matrix.");
            Matrix result = *this;
            for (size_t layer = 0; layer < Rows / 2; ++layer) {
            size_t first = layer;
            size_t last = Rows - 1 - layer;
            for (size_t i = first; i < last; ++i) {
                size_t offset = i - first;
                T top = result.data[first][i];

                // Right -> Top
                result.data[first][i] = result.data[i][last];

                // Bottom -> Right
                result.data[i][last] = result.data[last][last - offset];

                // Left -> Bottom
                result.data[last][last - offset] = result.data[last - offset][first];

                // Top -> Left
                result.data[last - offset][first] = top;
            }
            }
            return result;
        }


        // Overload the << operator for Matrix
        template <typename U, size_t R, size_t C>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<U, R, C>& matrix);

    };

    template <typename U, size_t R, size_t C>
    std::ostream& operator<<(std::ostream& os, const Matrix<U, R, C>& matrix) {
        for (const auto& row : matrix) {
            for (const auto& elem : row) {
                os << elem << " ";
            }
            os << "\n";
        }
        return os;
    }

} // namespace math

