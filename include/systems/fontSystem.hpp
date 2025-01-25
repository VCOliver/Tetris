#pragma once

#include "pch.h"
#include <SDL2/SDL_ttf.h>

#include "utils/colors.hpp"
#include "utils/position.hpp"

/**
 * @class FontSystem
 * @brief Static class that provides functionality for managing fonts, rendering text, and creating text surfaces using SDL_ttf.
 *
 * This class encapsulates font-related operations, allowing text rendering with configurable fonts and colors
 * in an SDL-based application. It uses SDL_ttf to handle font rendering.
 */
class FontSystem {
    static TTF_Font* font;           ///< Pointer to the currently loaded font.
    static char* m_fontPath;         ///< Path to the font file being used.
    static int m_size;               ///< Current font size.

public:
    /**
     * @brief Initializes the font system with the specified font and size.
     * 
     * @param fontPath Path to the font file (e.g., .ttf file).
     * @param size Font size (default is 20).
     * @return True if the initialization succeeds, false otherwise.
     */
    static bool Init(const char* fontPath, int size = 20);

    /**
     * @brief Shuts down the font system and frees allocated resources.
     *
     * This method should be called before the program exits to release the loaded font and other resources.
     */
    static void Shutdown();

    /**
     * @brief Updates the font size.
     * 
     * @param size New font size to set.
     * @return True if the font size was updated successfully, false otherwise.
     */
    static bool setFontSize(int size);

    /**
     * @brief Loads the current font using the stored font path and size.
     * 
     * @return True if the font is successfully loaded, false otherwise.
     */
    static bool loadFont();

    /**
     * @brief Loads a font from the specified font path.
     * 
     * @param fontPath Path to the font file to load.
     * @return True if the font is successfully loaded, false otherwise.
     */
    static bool loadFont(const char* fontPath);

    /**
     * @brief Creates an SDL_Surface containing the rendered text.
     * 
     * @param text The string to render.
     * @param color The color to use for the rendered text.
     * @return Pointer to an SDL_Surface containing the text, or nullptr on failure.
     */
    static SDL_Surface* createSurface(const std::string& text, Color color);

    /**
     * @brief Renders text directly onto the specified SDL_Renderer.
     * 
     * @param renderer The SDL_Renderer to render the text onto.
     * @param text The string to render.
     * @param pos The position on the renderer where the text should appear.
     * @param color The color of the text.
     */
    static void renderText(SDL_Renderer* renderer, const std::string& text, SDL_Point pos, Color color);

    /**
     * @brief Renders an SDL_Surface containing text onto the specified SDL_Renderer.
     * 
     * @param renderer The SDL_Renderer to render the surface onto.
     * @param surface The SDL_Surface containing the text.
     * @param pos The position on the renderer where the text should appear.
     * @param destroySurface If true, the surface will be destroyed after rendering. Default is false.
     */
    static void renderText(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Point pos, bool destroySurface = false);
};
