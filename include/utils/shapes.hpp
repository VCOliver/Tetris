#pragma once

#include "utils/mathUtils.hpp"

#define SHAPES_MATRIX_H 4
#define SHAPES_MATRIX_W 4

#define FILLED 1
#define EMPTY 0

namespace shapes{
    using s_matrix = math::Matrix<int, SHAPES_MATRIX_W, SHAPES_MATRIX_H>;
    
    inline const s_matrix square_tetromino = {{0, 0, 0, 0},
                                              {0, 1, 1, 0},
                                              {0, 1, 1, 0},
                                              {0, 0, 0, 0}};   

    inline const s_matrix L_tetromino = {{0, 0, 0, 0},
                                         {0, 1, 0, 0},
                                         {0, 1, 0, 0},
                                         {0, 1, 1, 0}};   

    inline const s_matrix inv_L_tetromino = {{0, 0, 0, 0},
                                             {0, 0, 1, 0},
                                             {0, 0, 1, 0},
                                             {0, 1, 1, 0}};

    inline const s_matrix straight_tetromino = {{0, 1, 0, 0},
                                                {0, 1, 0, 0},
                                                {0, 1, 0, 0},
                                                {0, 1, 0, 0}};

    inline const s_matrix T_tetromino = {{0, 0, 0, 0},
                                         {0, 1, 0, 0},
                                         {1, 1, 1, 0},
                                         {0, 0, 0, 0}}; 

    inline const s_matrix skew_tetromino = {{0, 0, 0, 0},
                                            {0, 1, 1, 0},
                                            {1, 1, 0, 0},
                                            {0, 0, 0, 0}}; 

    inline const s_matrix inv_skew_tetromino = {{0, 0, 0, 0},
                                                {0, 1, 1, 0},
                                                {0, 0, 1, 1},
                                                {0, 0, 0, 0}}; 
                                    

}