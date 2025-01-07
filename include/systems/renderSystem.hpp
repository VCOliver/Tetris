#pragma once

#include <vector>
#include <tuple>
#include <memory>

#include "utils/colors.hpp"
#include "utils/position.hpp"
#include "components/renderComponents.hpp"

#define STD_WIDTH 800
#define STD_HEIGHT 600

using renderComponent_ptr = std::shared_ptr<IRenderComponent>;
using coloredComponents = std::tuple<renderComponent_ptr, Color>;

namespace render {
    const Position getWindowCenter(SDL_Window* window);
}

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