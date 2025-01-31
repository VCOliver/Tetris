#include "entities/playfield.hpp"

#include "events/collisionEvent.hpp"

Playfield::Playfield(Position pos) : start_pos(pos), tetromino(nullptr){
    tetrion = std::make_unique<Tetrion>(pos);
}

Playfield::~Playfield(){
    delete tetromino;
}

void Playfield::spawnTetromino(){
    int x = std::rand() % (TETRION_W-SHAPES_MATRIX_W-1);
    x++;
    Position tetromino_pos = {start_pos.x+x, start_pos.y-1};
    tetromino = new Tetrominos(tetromino_pos, Colors::YELLOW);
}

void Playfield::onUpdate(){
    CollisionChecker collisionChecker(*tetromino, *tetrion);
    collisionChecker.checkCollision();
}

void Playfield::render() const {
    tetromino->render(); // Renders Tetromino    
    // Cover Tetromino part above Tetrion
    SDL_Point p = start_pos.getRealPosition();
    int w = (TETRION_W+1)*20;
    int h = p.y;
    p.y = 0;
    Renderer::setRenderDrawColor(Colors::BLACK);
    Renderer::SDL_FillRect(p, w, h);

    // // Renders Tetrion
    tetrion->render();
}