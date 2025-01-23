#pragma once

#include "pch.h"

#include "utils/colors.hpp"
#include "utils/position.hpp"
#include "utils/renderUtils.hpp"
#include "components/renderComponents.hpp"

#define STD_WIDTH 800
#define STD_HEIGHT 600

using renderables_ptr = std::shared_ptr<Renderable>;

/**
 * @class RenderSystem
 * @brief Manages and renders components using SDL_Renderer.
 */
class Renderer {

    static SDL_Renderer* renderer; ///< Pointer to the SDL_Renderer.

    static std::vector<renderables_ptr> renderComponents; ///< Vector of render components with associated colors.

public:
    /**
     * @brief Constructs a RenderSystem with the given SDL_Renderer.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     */
    static bool Init(SDL_Window* window);

    /**
     * @brief Destructor for the RenderSystem class.
     * 
     * This destructor is responsible for cleaning up any resources
     * that the RenderSystem class may have allocated during its lifetime.
     */
    static void Shutdown();

    static void setRenderDrawColor(Color color, rgba_t alpha=255);

    static void setDrawBlendMode(); // TODO

    /**
     * @brief Sets the background color for the renderer.
     * 
     * @param color The background color to set. Default is Colors::BLACK.
     */
    static void setBackground(Color color=Colors::BLACK);

    /// @brief Draw borders of Rectangle
    /// @param start_pos Position in Game coordinates
    /// @param width In pixels
    /// @param height In pixels
    static void DrawRect(Position start_pos, uint width, uint height);

    static void FillRect(Position start_pos, uint width, uint height);

    /**
     * @brief Adds a render component with the specified color.
     * 
     * @param component Shared pointer to the render component.
     */
    static void addRenderComponent(const renderables_ptr& component);

    /**
     * @brief Removes a render component.
     * 
     * @param component Shared pointer to the render component to remove.
     * 
     * @note Not in use
     */
    static void removeRenderComponent(const renderables_ptr& component);

    /**
     * @brief Clears all render components.
     */
    static void clearComponents();
    
    /**
     * @brief Renders all the components.
     */
    static void render();
};