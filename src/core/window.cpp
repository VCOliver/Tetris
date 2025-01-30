#include "core/window.hpp"

#include "pch.h"
#include "core/log.hpp"

Window::Window(const std::string& title, unsigned int width, unsigned int height)
    : title(title), width(width), height(height){
    window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        WINDOW_FLAGS
    );

    if (!window) {
        LOG_ERROR("SDL_CreateWindow Error: ", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    LOG_INFO("Initializing window!");

    data.title = title;
    data.height = height;
    data.width = width;

}

Window::~Window(){
    Shutdown();
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