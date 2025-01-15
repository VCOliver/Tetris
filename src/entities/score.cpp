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
            matrix(y, x) = std::make_tuple(p, visible);
            visible=false;
        }
    }
}

void ScoreBlock::increment_score(int points){
    this->score += points;
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
    fontSystem->renderText(renderer, "Score:", {p.x+30, p.y+20}, Colors::WHITE);
    fontSystem->renderText(renderer, std::to_string(score), {p.x+30, p.y+45}, Colors::WHITE);
}