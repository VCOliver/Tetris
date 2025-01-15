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
    fontSystem = new FontSystem();
    fontSystem->loadFont();

    stopwatch = new Stopwatch();
}   

void Game::run(){

    auto tetro = std::make_shared<Tetrominos>(Position(START_POSITION), Colors::PURPLE);
    auto score = std::make_shared<ScoreBlock>(Position(START_POSITION), fontSystem);

    auto watch = std::make_shared<StopwatchBlock>(Position{0, 4}, fontSystem);
    watch->setTime(0);

    // Start the stopwatch with a callback to update the clock
    stopwatch->start([&watch, this](int elapsed_seconds) {
        watch->setTime(elapsed_seconds);
    });

    renderSystem->addRenderComponent(score);
    renderSystem->addRenderComponent(watch);

    while(true){
        Uint32 frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        renderSystem->setBackground();

        score->increment_score(11);

        renderSystem->render();

        // Atualizar a tela
        SDL_RenderPresent(renderer);

        // Calculate frame duration
        Uint32 frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Delay to maintain 30 FPS
        }


    }
}

void Game::close(){
    // Clean up
    delete renderSystem;
    delete fontSystem;
    delete stopwatch;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

