#include <array>
#include <ctime>

#include "entities/tetrominos.hpp"

Tetrominos::Tetrominos(Position start_pos) : start_pos(start_pos){
    std::srand(std::time(nullptr)); // Seed the random number generator
}

shapes::Matrix Tetrominos::getRandomShape() const {
    std::array<char, 7> keys;
    int i;
    for(const auto& pair: shapes::shapes_map){
        keys[i] = pair.first;
        i++;
    }

    int randomIndex = std::rand() % keys.size();
    char randomKey = keys[randomIndex];
    return shapes::shapes_map.at(randomKey);

}