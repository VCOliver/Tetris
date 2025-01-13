#include <memory>
#include <vector>
#include <tuple>

#include "utils/colors.hpp"
#include "utils/position.hpp"
#include "utils/renderUtils.hpp"
#include "components/renderComponents.hpp"

#define STD_WIDTH 800
#define STD_HEIGHT 600

using renderComponent_ptr = std::shared_ptr<IRenderComponent>;
using coloredComponents = std::tuple<renderComponent_ptr, Color>;

/**
 * @class RenderSystem
 * @brief Manages and renders components using SDL_Renderer.
 */
class RenderSystem {

    SDL_Renderer* renderer; ///< Pointer to the SDL_Renderer.

    std::vector<coloredComponents> renderComponents; ///< Vector of render components with associated colors.

public:
    /**
     * @brief Constructs a RenderSystem with the given SDL_Renderer.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     */
    RenderSystem(SDL_Renderer* renderer);

    /**
     * @brief Destructor for the RenderSystem class.
     * 
     * This destructor is responsible for cleaning up any resources
     * that the RenderSystem class may have allocated during its lifetime.
     */
    ~RenderSystem();

    /**
     * @brief Sets the background color for the renderer.
     * 
     * @param color The background color to set. Default is Colors::BLACK.
     */
    void setBackground(Color color=Colors::BLACK);

    /**
     * @brief Adds a render component with the specified color.
     * 
     * @param component Shared pointer to the render component.
     * @param color The color associated with the component.
     */
    void addRenderComponent(const renderComponent_ptr& component, Color color);

    /**
     * @brief Removes a render component.
     * 
     * @param component Shared pointer to the render component to remove.
     * 
     * @note Not in use
     */
    void removeRenderComponent(const renderComponent_ptr& component);

    /**
     * @brief Clears all render components.
     */
    void clearComponents();
    
    /**
     * @brief Renders all the components.
     */
    void render() const;
};