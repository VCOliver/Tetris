#pragma once

#include <vector>
#include <tuple>
#include <memory>

#include "utils/colors.hpp"
#include "components/renderComponents.hpp"

using renderComponent_ptr = std::shared_ptr<IRenderComponent>;
using coloredComponents = std::tuple<renderComponent_ptr, Color>;

class RenderSystem {

    SDL_Renderer* renderer;

    std::vector<coloredComponents> renderComponents;

public:
    RenderSystem(SDL_Renderer* renderer);

    void setBackground(Color color);

    // Component related
    void addRenderComponent(const renderComponent_ptr& component, Color color);
    void removeRenderComponent(const renderComponent_ptr& component);
    void clearComponents();
    
    void render();
};