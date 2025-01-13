#pragma once

#include <unordered_map>

#include "utils/mathUtils.hpp"

#define SHAPES_MATRIX_H 4
#define SHAPES_MATRIX_W 4

#define FILLED 1
#define EMPTY 0

namespace shapes{
    using Matrix = math::Matrix<int, SHAPES_MATRIX_H, SHAPES_MATRIX_W>;
    
    inline const Matrix square_tetromino = {{0, 0, 0, 0},
                                            {0, 1, 1, 0},
                                            {0, 1, 1, 0},
                                            {0, 0, 0, 0}};   

    inline const Matrix L_tetromino = {{0, 0, 0, 0},
                                       {0, 1, 0, 0},
                                       {0, 1, 0, 0},
                                       {0, 1, 1, 0}};   

    inline const Matrix inv_L_tetromino = {{0, 0, 0, 0},
                                           {0, 0, 1, 0},
                                           {0, 0, 1, 0},
                                           {0, 1, 1, 0}};

    inline const Matrix straight_tetromino = {{0, 1, 0, 0},
                                              {0, 1, 0, 0},
                                              {0, 1, 0, 0},
                                              {0, 1, 0, 0}};

    inline const Matrix T_tetromino = {{0, 0, 0, 0},
                                       {0, 1, 0, 0},
                                       {1, 1, 1, 0},
                                       {0, 0, 0, 0}}; 

    inline const Matrix skew_tetromino = {{0, 0, 0, 0},
                                          {0, 1, 1, 0},
                                          {1, 1, 0, 0},
                                          {0, 0, 0, 0}}; 

    inline const Matrix inv_skew_tetromino = {{0, 0, 0, 0},
                                              {0, 1, 1, 0},
                                              {0, 0, 1, 1},
                                              {0, 0, 0, 0}}; 
                                    
    const std::unordered_map<char, Matrix> shapes_map = {{'O', square_tetromino},
                                                         {'L', L_tetromino},
                                                         {'J', inv_L_tetromino},
                                                         {'I', straight_tetromino},
                                                         {'T', T_tetromino},
                                                         {'S', skew_tetromino},
                                                         {'Z', inv_skew_tetromino}};

}