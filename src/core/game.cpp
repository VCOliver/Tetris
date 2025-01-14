#include <iostream>
#include <mutex>

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

    std::mutex time_mutex;
    std::string time = "00:00";
    std::string current_time = time;

    // Start the stopwatch with a callback to update the clock
    stopwatch->start([&time, &time_mutex](int elapsed_seconds) {
        int mins = elapsed_seconds / 60;
        int secs = elapsed_seconds % 60;
        {
            std::lock_guard<std::mutex> lock(time_mutex);
            time = (mins < 10 ? "0" : "") + std::to_string(mins) + ":" + (secs < 10 ? "0" : "") + std::to_string(secs);
        }
    });

    while(true){
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
        }

        renderSystem->setBackground();

        //const Position center = render::getWindowCenter(window);
        const Position center = START_POSITION;
        auto block1 = std::make_shared<Block>(center, Colors::RED);
        auto block2 = std::make_shared<Block>(Position{center.x+1, center.y}, Colors::CYAN);
        auto block3 = std::make_shared<Block>(Position{center.x+2, center.y}, Colors::ORANGE);
        auto block4 = std::make_shared<Block>(Position{center.x+1, center.y+1}, Colors::PURPLE);
        auto block5 = std::make_shared<Block>(Position{center.x+2, center.y+1}, Colors::YELLOW);
        auto block6 = std::make_shared<Block>(Position{center.x, center.y+1}, Colors::GREEN);
        auto block7 = std::make_shared<Block>(Position{center.x+3, center.y}, Colors::GRAY);
        auto block8 = std::make_shared<Block>(Position{center.x+3, center.y+1}, Colors::GRAY);
        auto block9 = std::make_shared<Block>(Position{center.x+1, center.y+2}, Colors::PURPLE);
        auto block10 = std::make_shared<Block>(Position{center.x+2, center.y+2}, Colors::YELLOW);
        auto block11 = std::make_shared<Block>(Position{center.x, center.y+2}, Colors::GREEN);
        auto block12 = std::make_shared<Block>(Position{center.x+3, center.y+2}, Colors::GRAY);

        auto wall = std::make_shared<Tetrion>(Position(START_POSITION));
        

        //renderSystem->addRenderComponent(wall, Colors::GRAY);
        // renderSystem->addRenderComponent(tetro);

        // renderSystem->addRenderComponent(block1);
        // renderSystem->addRenderComponent(block2);
        // renderSystem->addRenderComponent(block3);
        // renderSystem->addRenderComponent(block4);
        // renderSystem->addRenderComponent(block5);
        // renderSystem->addRenderComponent(block6);
        // renderSystem->addRenderComponent(block7);
        // renderSystem->addRenderComponent(block8);
        // renderSystem->addRenderComponent(block9);
        // renderSystem->addRenderComponent(block10);
        // renderSystem->addRenderComponent(block11);
        // renderSystem->addRenderComponent(block12);


        //renderSystem->render();

        //Write to screen
        //fontSystem->renderText(renderer, "Hello, world!", Position(START_POSITION), Colors::WHITE);
        {
            std::lock_guard<std::mutex> lock(time_mutex);
            current_time = time;
        }
        fontSystem->renderText(renderer, current_time, Position(START_POSITION), Colors::WHITE);

        // Atualizar a tela
        SDL_RenderPresent(renderer);
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

