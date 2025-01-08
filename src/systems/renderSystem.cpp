#include <algorithm>
#include <iostream>

#include "systems/renderSystem.hpp"

RenderSystem::RenderSystem(SDL_Renderer* renderer)
    : renderer(renderer){}

void RenderSystem::setBackground(Color color){
    // Limpar a tela
    render::setRenderDrawColor(renderer, color); // Cor preta para o fundo
    SDL_RenderClear(renderer);
}

void RenderSystem::addRenderComponent(const renderComponent_ptr& component, Color color){
    renderComponents.emplace_back(component, color);
}

void RenderSystem::removeRenderComponent(const renderComponent_ptr& component) {
    renderComponents.erase(std::remove_if(
        renderComponents.begin(), renderComponents.end(),
        [&component](const coloredComponents& item) {
            return std::get<0>(item) == component;
        }),
        renderComponents.end());
}

void RenderSystem::clearComponents(){
    renderComponents.clear();
}

void RenderSystem::render() const {
    for (const auto& [component, color] : renderComponents) {
        // Set the color for this component
        render::setRenderDrawColor(renderer, color);
        
        // Render the component
        if (component) {
            component->render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}
