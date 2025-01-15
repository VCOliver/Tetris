#include <algorithm>
#include <iostream>

#include "systems/renderSystem.hpp"

RenderSystem::RenderSystem(SDL_Renderer* renderer)
    : renderer(renderer){}

RenderSystem::~RenderSystem(){
    this->clearComponents();
}

void RenderSystem::setBackground(Color color){
    // Limpar a tela
    render::setRenderDrawColor(renderer, color); // Cor para o fundo
    SDL_RenderClear(renderer);
}

void RenderSystem::addRenderComponent(const renderables_ptr& component){
    renderComponents.emplace_back(component);
}

void RenderSystem::removeRenderComponent(const renderables_ptr& component) {
    renderComponents.erase(std::remove_if(
        renderComponents.begin(), renderComponents.end(),
        [&component](const renderables_ptr& item) {
            return item == component;
        }),
        renderComponents.end());
}

void RenderSystem::clearComponents(){
    renderComponents.clear();
}

void RenderSystem::render() const {
    for (const auto& component : renderComponents) {

        // Render the component
        if (component) {
            component->render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}
