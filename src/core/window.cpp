#include "core/window.hpp"

#include "pch.h"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : title(title), width(width), height(height){
    window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_RESIZABLE| SDL_WINDOW_HIDDEN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    std::cout << "Initializing window!" << std::endl;

    data.title = title;
    data.height = height;
    data.width = width;

}

Window::~Window(){
    shutdown();
}

void Window::shutdown(){
    SDL_DestroyWindow(window);
}

unsigned int Window::getHeight() const {
    return height;
}

unsigned int Window::getWidth() const {
    return width;
}

const Position Window::getWindowCenter(){
    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
    w /= 2;
    h /= 2;
    w /= STD_BLOCK_W;
    h /= STD_BLOCK_H;
    return {w, h};
}

void Window::setEventCallback(const EventCallback& callback){
    data.eventCallback = callback; 
}