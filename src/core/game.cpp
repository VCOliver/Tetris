#include <iostream>

#include "core/game.hpp"

Game::Game(int w, int h) : width(w), height(h){}

void Game::init(){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    window = std::make_unique<Window>("Tetris", width, height);

    window->setEventCallback(BIND_EVENT_FN(Game::processEvents));

    if(!Renderer::Init(window->getSDL_Window())){ TERMINATE_GAME(EXIT_FAILURE) }

    if(!FontSystem::Init(fontPath)){ TERMINATE_GAME(EXIT_FAILURE) }

    stopwatch = new Stopwatch();

    auto inputMapping = std::make_unique<InputMapping>();
    inputManager = new InputManager(std::move(inputMapping));

    std::srand(std::time(nullptr)); // Seed the random number generator
    std::cout << "Game initialized!" << std::endl;
}   

void Game::processEvents(){
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        auto event = TranslateSDLEvent(sdlEvent); // Custom function translating SDL to Hazel events
        if (event)
        {
            eventQueue.push(std::move(event));
        }
    }
}

void Game::update()
{
    while (!eventQueue.empty())
    {
        auto& event = eventQueue.front();
        EventDispatcher dispatcher(*event);

        dispatcher.Dispatch<KeyEvent>([this](KeyEvent* e) {
            inputManager->onEvent(e);
            return true; // Mark as handled
        });

        dispatcher.Dispatch<WindowResizeEvent>([](WindowResizeEvent& e){
            std::cout << e.ToString() << std::endl;
            return true;
        });

        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Game::onWindowClose));

        eventQueue.pop();
    }
}


void Game::run(){

    const Position tetrion_pos = {14, 3};
    const Position score_pos = {tetrion_pos.x+TETRION_W, tetrion_pos.y};
    const Position watch_pos = {score_pos.x, score_pos.y+4};

    auto field = std::make_shared<Playfield>(tetrion_pos);
    auto score = std::make_shared<ScoreBlock>(score_pos);
    auto watch = std::make_shared<StopwatchBlock>(watch_pos);
    watch->setTime(0);

    // Start the stopwatch with a callback to update the clock
    stopwatch->start([&watch, this](int elapsed_seconds) {
        watch->setTime(elapsed_seconds);
    });

    Renderer::addRenderComponent(field);
    Renderer::addRenderComponent(score);
    Renderer::addRenderComponent(watch);

    window->showWindow();

    while(running){
        Uint32 frameStart = SDL_GetTicks();

        processEvents();
        update();

        Renderer::setBackground();

        score->increment_score(2);

        // Draw on the screen
        Renderer::render();
        Renderer::RenderPresent();

        // Calculate frame duration
        Uint32 frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - frameTime); // Delay to maintain 60 FPS
        }


    }
}

bool Game::onWindowClose(WindowCloseEvent& e)
{
    std::cout << "Window close event!" << std::endl;
    running = false;
    return true;
}


void Game::close(){
    // Clean up
    GAME_SHUTDOWN
    delete stopwatch;
    delete inputManager;
}

