#pragma once

#include <vector>
#include <memory>

#include "components/renderComponents.hpp"

using renderComponent_ptr = std::shared_ptr<IRenderComponent>;

class RenderSystem {

    SDL_Renderer* renderer;

    std::vector<renderComponent_ptr> renderComponents;

public:
    RenderSystem(SDL_Renderer* renderer);

    void setBackground();

    // Component related
    void addRenderComponent(const renderComponent_ptr& component);
    void removeRenderComponent(const renderComponent_ptr& component);
    void clearComponents();
    
    void render();
};