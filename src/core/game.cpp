#include <iostream>

#include "core/game.hpp"
#include "components/renderComponents.hpp"

Game::Game(int w, int h) : width(w), height(h){}

void Game::init(){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = SDL_CreateWindow(
        "SDL2 Tutorial",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
}

void Game::run(){

    while(true){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        // Limpar a tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Cor preta para o fundo
        SDL_RenderClear(renderer);

        // Definir cor para o quadrado
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Cor vermelha

        // Definir o retângulo (quadrado)
        SDL_Rect square = { 0, 0, 20, 20 }; // x, y, largura, altura

        // Desenhar o quadrado (bordas)
        SDL_RenderDrawRect(renderer, &square);

        // Preencher o quadrado (opcional)
        SDL_RenderFillRect(renderer, &square);

        // Definir o retângulo (quadrado)
        square = { 20, 0, 20, 20 }; // x, y, largura, altura

        // Desenhar o quadrado (bordas)
        SDL_RenderDrawRect(renderer, &square);

        // Preencher o quadrado (opcional)
        SDL_RenderFillRect(renderer, &square);

        // Atualizar a tela
        SDL_RenderPresent(renderer);
    }
}

void Game::close(){
        // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

