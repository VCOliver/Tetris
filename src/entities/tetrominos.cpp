#include <array>
#include <ctime>

#include "entities/tetrominos.hpp"

Tetrominos::Tetrominos(Position start_pos, Color color) 
    : start_pos(start_pos), color(color){
    auto shape = getRandomShape();
    for(int y = 0; y<SHAPES_MATRIX_H; y++){
        for(int x = 0; x<SHAPES_MATRIX_W; x++){
            Position p = {start_pos.x + x, start_pos.y + y};
            bool visible = shape(y, x);
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
    std::cout << "Moving Tetromino instance down!" << std::endl;
    for(auto& row : matrix){
        for(auto& [pos, _] : row){
            pos.y += 1;
        }
    }
}

void Tetrominos::moveLeft(){
    std::cout << "Moving Tetromino instance left!" << std::endl;
    for(auto& row : matrix){
        for(auto& [pos, _] : row){
            pos.x -= 1;
        }
    }
}

void Tetrominos::moveRight(){
    std::cout << "Moving Tetromino instance right!" << std::endl;
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
            std::cout << "Invalid direction!" << std::endl;
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