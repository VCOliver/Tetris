#include <iostream>

#include "core/game.hpp"

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

    renderSystem = new RenderSystem(renderer);

}

void Game::run(){

    while(true){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        renderSystem->setBackground(Colors::BLACK);

        auto block1 = std::make_shared<Block>(Position{STD_WIDTH/40, STD_HEIGHT/40});
        auto block2 = std::make_shared<Block>(Position{0, 0});

        renderSystem->addRenderComponent(block1, Colors::RED);
        renderSystem->addRenderComponent(block2, Colors::CYAN);

        renderSystem->render();

        // Atualizar a tela
        SDL_RenderPresent(renderer);
    }
}

void Game::close(){
    // Clean up
    delete renderSystem;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

