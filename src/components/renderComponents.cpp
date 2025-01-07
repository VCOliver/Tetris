#include <iostream>

#include "components/renderComponents.hpp"
#include "utils/colors.hpp"

Block::Block(Position pos, int w, int h, int alpha)
            : pos(pos), width(w), height(h){
    if(alpha > 255 || alpha < 0){
        std::cerr << "Opacity cannot be lower than 0\% or greater than 100\%" << std::endl;
        exit(1);
    }

    this->alpha = alpha;
}

void Block::render(SDL_Renderer* renderer) const {
    int x = this->pos.x * 20;
    int y = this->pos.y * 20;
    int h = this->height;
    int w = this->width;

    // Definir o retângulo (quadrado)
    SDL_Rect square = { x, y, w, h }; // x, y, largura, altura

    // Desenhar o quadrado (bordas)
    SDL_RenderDrawRect(renderer, &square);

    // Preencher o quadrado
    SDL_RenderFillRect(renderer, &square);

    Color color = Colors::WHITE;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable blending mode
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 127);
    SDL_Point points[] = {{x, y+STD_BLOCK_H}, {x, y}, {x+STD_BLOCK_W, y}};
    SDL_RenderDrawLines(renderer, points, 3);

    // Deactivate blending mode
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}