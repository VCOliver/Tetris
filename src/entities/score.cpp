#include "entities/score.hpp"

ScoreBlock::ScoreBlock(Position pos, FontSystem* fontSystem)
    : start_pos(pos), score(0), fontSystem(fontSystem)
{
    bool visible = false;
    for(int y=0; y<h; y++){
        for(int x=0; x<w; x++){
            Position p = {start_pos.x + x, start_pos.y + y};
            if(x == 0 || y == 0 || x == w-1 || y == h-1){
                visible=true;
            }
            matrix(x, y) = std::make_tuple(p, visible);
            visible=false;
        }
    }
}

void ScoreBlock::increment_score(int points){
    int temp = (score+points) % 10000000;
    this->score = temp;
}

void ScoreBlock::render(SDL_Renderer* renderer) const {
    for(auto& row : matrix){
        for(auto& [pos, visible] : row){
            if(visible){
                Block block = Block(pos, Colors::GRAY);
                block.render(renderer);
            }
        }
    }
    SDL_Point p = start_pos.getRealPosition();
    fontSystem->renderText(renderer, "Score:", {p.x+40, p.y+20}, Colors::WHITE);
    SDL_Surface* surface = fontSystem->createSurface(std::to_string(score), Colors::WHITE);
    p = Position({start_pos.x + w-1, start_pos.y+2}).getRealPosition();
    p.x -= surface->w + 7;
    p.y += 5;
    fontSystem->renderText(renderer, surface, p, true);
}