#include <array>
#include <ctime>

#include "entities/tetrominos.hpp"
#include "core/log.hpp"

Tetrominos::Tetrominos(Position start_pos, Color color) 
    : start_pos(start_pos), color(color){
    shape = getRandomShape();
    for(int y = 0; y<SHAPES_MATRIX_H; y++){
        for(int x = 0; x<SHAPES_MATRIX_W; x++){
            Position p = {start_pos.x + x, start_pos.y + y};
            bool visible = shape(x, y);
            matrix(x, y) = std::make_tuple(p, visible);
        }
    }
}

Tetrominos::Tetrominos(Position start_pos, Color color, shapes::Matrix shape) 
    : start_pos(start_pos), color(color){
    for(int y = 0; y<SHAPES_MATRIX_H; y++){
        for(int x = 0; x<SHAPES_MATRIX_W; x++){
            Position p = {start_pos.x + x, start_pos.y + y};
            bool visible = shape(x, y);
            matrix(x, y) = std::make_tuple(p, visible);
        }
    }
}

shapes::Matrix Tetrominos::getRandomShape() const {
    std::array<char, 7> keys;
    int i=0;
    for(const auto& pair: shapes::shapes_map){
        keys[i] = pair.first;
        i++;
    }

    int randomIndex = std::rand() % keys.size();
    char randomKey = keys[randomIndex];
    return shapes::shapes_map.at(randomKey);

}

void Tetrominos::moveDown(){
    LOG_DEBUG("Moving Tetromino instance down!");
    for(auto& row : matrix){
        for(auto& [pos, _] : row){
            pos.y += 1;
        }
    }
}

void Tetrominos::moveLeft(){
    LOG_DEBUG("Moving Tetromino instance left!");
    for(auto& row : matrix){
        for(auto& [pos, _] : row){
            pos.x -= 1;
        }
    }
}

void Tetrominos::moveRight(){
    LOG_DEBUG("Moving Tetromino instance right!");
    for(auto& row : matrix){
        for(auto& [pos, _] : row){
            pos.x += 1;
        }
    }
}

void Tetrominos::move(Dir dir){
    switch(dir){
        case DOWN:
            moveDown();
            break;
        case LEFT:
            moveLeft();
            break;
        case RIGHT:
            moveRight();
            break;
        default:
            LOG_ERROR("Invalid direction!");
            break;
    }
}

void Tetrominos::rotateClockwise(){
    LOG_DEBUG("Rotating Tetromino instance clockwise!");
    this->shape = this->shape.rotateClockwise();
    for(int y = 0; y<SHAPES_MATRIX_H; y++){
        for(int x = 0; x<SHAPES_MATRIX_W; x++){
            Position p = std::get<0>(matrix(x, y));
            bool visible = shape(x, y);
            matrix(x, y) = std::make_tuple(p, visible);
        }
    }
}

void Tetrominos::rotateCounterClockwise(){
    LOG_DEBUG("Rotating Tetromino instance counterclockwise!");
    this->shape = this->shape.rotateCounterclockwise();
    for(int y = 0; y<SHAPES_MATRIX_H; y++){
        for(int x = 0; x<SHAPES_MATRIX_W; x++){
            Position p = std::get<0>(matrix(x, y));
            bool visible = shape(x, y);
            matrix(x, y) = std::make_tuple(p, visible);
        }
    }
}

void Tetrominos::rotate(Dir rollDir){
    switch(rollDir){
        case ROTATE_CLOCKWISE:
            rotateClockwise();
            break;
        case ROTATE_COUNTERCLOCKWISE:
            rotateCounterClockwise();
            break;
        default:
            LOG_DEBUG("Invalid direction!");
            break;
    }
}

void Tetrominos::render() const {
    for(auto& row : matrix){
        for(auto& [pos, visible] : row){
            if(visible){
                Block block = Block(pos,color);
                block.render();
            }
        }
    }
}