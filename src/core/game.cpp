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

    renderer = SDL_CreateRenderer(
        window->getSDL_Window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        close();
    }

    renderSystem = new RenderSystem(renderer);
    fontSystem = new FontSystem();
    fontSystem->loadFont();

    stopwatch = new Stopwatch();

    auto inputMapping = std::make_unique<InputMapping>();
    inputManager = new InputManager(std::move(inputMapping));

    std::srand(std::time(nullptr)); // Seed the random number generator
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

        dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) {
            std::cout << e.ToString() << std::endl; 
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
    auto score = std::make_shared<ScoreBlock>(score_pos, fontSystem);
    auto watch = std::make_shared<StopwatchBlock>(watch_pos, fontSystem);
    watch->setTime(0);

    // Start the stopwatch with a callback to update the clock
    stopwatch->start([&watch, this](int elapsed_seconds) {
        watch->setTime(elapsed_seconds);
    });

    renderSystem->addRenderComponent(field);
    renderSystem->addRenderComponent(score);
    renderSystem->addRenderComponent(watch);


    while(running){
        Uint32 frameStart = SDL_GetTicks();

        processEvents();
        update();

        renderSystem->setBackground();

        score->increment_score(2);

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

bool Game::onWindowClose(WindowCloseEvent& e)
	{
        std::cout << "Window close event!" << std::endl;
		running = false;
		return true;
	}


void Game::close(){
    // Clean up
    delete renderSystem;
    delete fontSystem;
    delete stopwatch;
    delete inputManager;
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

