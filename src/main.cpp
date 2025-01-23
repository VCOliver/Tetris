#include <iostream>

#include "core/base.hpp"
#include "core/game.hpp"

int main(){
    Game game = Game(STD_WINDOW_WIDTH, STD_WINDOW_HEIGHT);
    game.init();
    game.run();
    game.close();
}