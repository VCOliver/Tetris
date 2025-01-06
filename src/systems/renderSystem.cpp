#include <algorithm>

#include "systems/renderSystem.hpp"

RenderSystem::RenderSystem(SDL_Renderer* renderer)
    : renderer(renderer){}

void RenderSystem::setBackground(){
    // Limpar a tela
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Cor preta para o fundo
    SDL_RenderClear(renderer);
}

void RenderSystem::addRenderComponent(const renderComponent_ptr& component){
    renderComponents.push_back(component);
}

void RenderSystem::removeRenderComponent(const renderComponent_ptr& component){
    auto it = std::find(renderComponents.begin(), renderComponents.end(), component);
    if (it != renderComponents.end()) {
        renderComponents.erase(it);
    }
}

void RenderSystem::clearComponents(){
    renderComponents.clear();
}

void RenderSystem::render(){
    for (const auto& component : renderComponents) {
        component->render(renderer); // Call the appropriate render function polymorphically
    }
}