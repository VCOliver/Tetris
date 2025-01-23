#include <algorithm>
#include <iostream>

#include "systems/renderSystem.hpp"

bool Renderer::Init(SDL_Window* window){
    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void Renderer::Shutdown(){
    clearComponents();
    SDL_DestroyRenderer(renderer);
}

void Renderer::setDrawBlendMode(BlendMode mode){
    SDL_SetRenderDrawBlendMode(renderer, *(SDL_BlendMode*)mode);
}

void Renderer::setRenderDrawColor(Color color, rgba_t alpha){
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, alpha);
}

void Renderer::setBackground(Color color){
    // Limpar a tela
    setRenderDrawColor(color); // Cor para o fundo
    SDL_RenderClear(renderer);
}

void Renderer::DrawRect(Position start_pos, uint width, uint height){
    auto real_pos = start_pos.getRealPosition();
    SDL_Rect rect = {real_pos.x, real_pos.y, width, height}; // x, y, width, height
    SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::FillRect(Position start_pos, uint width, uint height){
    auto real_pos = start_pos.getRealPosition();
    SDL_Rect rect = {real_pos.x, real_pos.y, width, height}; // x, y, width, height
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::FillTrapz(const math::Trapezium& trapezium) {
    int minX = SDL_min(SDL_min(trapezium.top_left.x, trapezium.top_right.x), SDL_min(trapezium.bottom_left.x, trapezium.bottom_right.x));
    int maxX = SDL_max(SDL_max(trapezium.top_left.x, trapezium.top_right.x), SDL_max(trapezium.bottom_left.x, trapezium.bottom_right.x));
    int minY = SDL_min(SDL_min(trapezium.top_left.y, trapezium.top_right.y), SDL_min(trapezium.bottom_left.y, trapezium.bottom_right.y));
    int maxY = SDL_max(SDL_max(trapezium.top_left.y, trapezium.top_right.y), SDL_max(trapezium.bottom_left.y, trapezium.bottom_right.y));

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (math::isPointInTrapezium(x, y, trapezium)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void Renderer::DrawTrapz(const math::Trapezium& trapz){
    SDL_RenderDrawLine(renderer, trapz.top_left.x, trapz.top_left.y, trapz.top_right.x, trapz.top_right.y);
    SDL_RenderDrawLine(renderer, trapz.top_right.x, trapz.top_right.y, trapz.bottom_right.x, trapz.bottom_right.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_right.x, trapz.bottom_right.y, trapz.bottom_left.x, trapz.bottom_left.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_left.x, trapz.bottom_left.y, trapz.top_left.x, trapz.top_left.y);
}

void Renderer::addRenderComponent(const renderables_ptr& component){
    renderComponents.emplace_back(component);
}

void Renderer::removeRenderComponent(const renderables_ptr& component) {
    renderComponents.erase(std::remove_if(
        renderComponents.begin(), renderComponents.end(),
        [&component](const renderables_ptr& item) {
            return item == component;
        }),
        renderComponents.end());
}

void Renderer::clearComponents(){
    renderComponents.clear();
}

void Renderer::render() {
    for (const auto& component : renderComponents) {

        // Render the component
        if (component) {
            component->render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}
