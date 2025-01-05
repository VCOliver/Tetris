#include <SDL2/SDL.h>
#include <iostream>

int main(){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Tutorial",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800,
        600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main loop
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

                // Limpar a tela
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Cor preta para o fundo
        SDL_RenderClear(renderer);

        // Definir cor para o quadrado
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Cor vermelha

        // Definir o retângulo (quadrado)
        SDL_Rect square = { 300, 200, 10, 10 }; // x, y, largura, altura

        // Desenhar o quadrado (bordas)
        SDL_RenderDrawRect(renderer, &square);

        // Preencher o quadrado (opcional)
        SDL_RenderFillRect(renderer, &square);

        // Atualizar a tela
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}