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

    std::srand(std::time(nullptr)); // Seed the random number generator
}   

void Game::run(){

    const auto tetrion_pos = Position({14, 3});
    const auto score_pos = Position({tetrion_pos.x+TETRION_W, tetrion_pos.y});
    const auto watch_pos = Position({score_pos.x, score_pos.y+4});
    int x = std::rand() % (TETRION_W-1);
    const auto tetro_pos = Position({tetrion_pos.x + x, 2});

    auto wall = std::make_shared<Tetrion>(tetrion_pos);
    auto tetro = std::make_shared<Tetrominos>(tetro_pos, Colors::RED);
    auto score = std::make_shared<ScoreBlock>(score_pos, fontSystem);
    auto watch = std::make_shared<StopwatchBlock>(watch_pos, fontSystem);
    watch->setTime(0);

    // Start the stopwatch with a callback to update the clock
    stopwatch->start([&watch, this](int elapsed_seconds) {
        watch->setTime(elapsed_seconds);
    });

    renderSystem->addRenderComponent(tetro);
    renderSystem->addRenderComponent(wall);
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

        score->increment_score(91119);

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

