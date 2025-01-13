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
        "Tetris",
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

    auto tetro = std::make_shared<Tetrominos>(Position(START_POSITION), Colors::PURPLE);

    while(true){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        renderSystem->setBackground();

        const Position center = render::getWindowCenter(window);
        auto block1 = std::make_shared<Block>(center, Colors::RED);
        auto block2 = std::make_shared<Block>(Position{center.x+1, center.y}, Colors::CYAN);
        auto block3 = std::make_shared<Block>(Position{center.x-1, center.y}, Colors::ORANGE);
        auto block4 = std::make_shared<Block>(Position{center.x+1, center.y-1}, Colors::PURPLE);
        auto block5 = std::make_shared<Block>(Position{center.x-1, center.y-1}, Colors::YELLOW);
        auto block6 = std::make_shared<Block>(Position{center.x, center.y-1}, Colors::GREEN);

        auto wall = std::make_shared<Tetrion>(Position(START_POSITION));
        

        //renderSystem->addRenderComponent(wall, Colors::GRAY);
        // renderSystem->addRenderComponent(tetro);

        renderSystem->addRenderComponent(block1);
        renderSystem->addRenderComponent(block2);
        renderSystem->addRenderComponent(block3);
        renderSystem->addRenderComponent(block4);
        renderSystem->addRenderComponent(block5);
        renderSystem->addRenderComponent(block6);


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

