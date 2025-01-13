#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"
#include "utils/colors.hpp"
#include "components/renderComponents.hpp"

using Renderable = IRenderComponent;

/**
 * @struct Triangle
 * @brief Represents a triangle using three SDL_Point vertices.
 */
struct Triangle {
    SDL_Point v1; ///< Vertex 1 of the triangle
    SDL_Point v2; ///< Vertex 2 of the triangle
    SDL_Point v3; ///< Vertex 3 of the triangle
};

namespace render {

    /**
     * @brief Gets the center Position for possible block coordinates of the given SDL_Window.
     * 
     * @param window Pointer to the SDL_Window.
     * @return Position The center position of the window.
     */
    const Position getWindowCenter(SDL_Window* window);

    /**
     * @brief Sets the drawing color for rendering.
     * 
     * This function sets the color used for renderer drawing operations.
     * 
     * @param renderer A pointer to the SDL_Renderer structure that represents the rendering context.
     * @param color The Color structure representing the RGB color to be used.
     * @param alpha The alpha value (transparency) to be used. Default is OPAQUE.
     */
    void setRenderDrawColor(SDL_Renderer* renderer, Color color, rgba_t alpha=OPAQUE);

    /**
     * @brief Renders the outline of a trapezium using the given SDL_Renderer.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     * @param trapz The trapezium to be rendered.
     */
    void renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz);

    /**
     * @brief Renders a filled trapezium using the given SDL_Renderer.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     * @param trapezium The trapezium to be filled and rendered.
     */
    void renderFillTrapz(SDL_Renderer* renderer, const Trapezium& trapezium);

    /**
     * @brief Checks if a point is inside a given trapezium.
     * 
     * @param px X-coordinate of the point.
     * @param py Y-coordinate of the point.
     * @param trapezium The trapezium to check against.
     * @return int Returns true if the point is inside the trapezium, otherwise false.
     */
    bool isPointInTrapezium(int px, int py, const Trapezium& trapezium);

    /**
     * @brief Checks if a point is inside a given triangle.
     * 
     * @param p The point to check.
     * @param tri The triangle to check against.
     * @return int Returns true if the point is inside the triangle, otherwise false.
     */
    bool isPointInTriangle(SDL_Point p, Triangle& tri);
}