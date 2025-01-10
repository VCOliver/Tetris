#pragma once

#include <array>
#include <initializer_list>

#include "position.hpp"

namespace math {

    /// @brief Calculates the distance between 2 points
    /// @param p1 Point 1
    /// @param p2 Point 2
    /// @return The distance from one point to the other
    /// @note Not being used
    float calculateDistace(Position& p1, Position& p2);

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
        T& operator()(size_t row, size_t col) {
            return data[row][col];
        }

        const T& operator()(size_t row, size_t col) const {
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

