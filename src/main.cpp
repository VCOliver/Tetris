#include <iostream>

#include "core/game.hpp"

int main(){
    Game game = Game(STD_WIDTH, STD_HEIGHT);
    game.init();
    game.run();
    game.close();
}