#include <algorithm>
#include <iostream>

#include "utils/renderUtils.hpp"
#include "utils/mathUtils.hpp"

const Position render::getWindowCenter(SDL_Window* window){
    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
    w /= 2;
    h /= 2;
    // w -= (STD_BLOCK_W/2);
    // h -= (STD_BLOCK_H/2);
    w /= STD_BLOCK_W;
    h /= STD_BLOCK_H;
    return {w, h};
}

void render::renderFillTrapz(SDL_Renderer* renderer, Trapezium trapz) {
    Position top_left = trapz.top_left.getRealPosition();
    Position top_right = trapz.top_right.getRealPosition();
    Position bottom_left = trapz.bottom_left.getRealPosition();
    Position bottom_right = trapz.bottom_right.getRealPosition();

    std::cout << "Top Left: (" << top_left.x << ", " << top_left.y << ")" << std::endl;
    std::cout << "Top Right: (" << top_right.x << ", " << top_right.y << ")" << std::endl;
    std::cout << "Bottom Left: (" << bottom_left.x << ", " << bottom_left.y << ")" << std::endl;
    std::cout << "Bottom Right: (" << bottom_right.x << ", " << bottom_right.y << ")" << std::endl;

    // Calculate the slopes of the left and right sides
    float left_slope = (bottom_left.y != top_left.y) ? static_cast<float>(bottom_left.x - top_left.x) / (bottom_left.y - top_left.y) : 0;
    float right_slope = (bottom_right.y != top_right.y) ? static_cast<float>(bottom_right.x - top_right.x) / (bottom_right.y - top_right.y) : 0;

    // Ensure the loop condition is valid
    if (top_left.y > bottom_left.y || top_right.y > bottom_right.y) {
        std::cerr << "Invalid trapezium coordinates: top vertices must be above bottom vertices." << std::endl;
        return;
    }

    // Draw horizontal lines from top to bottom
    for (int y = top_left.y; y <= bottom_left.y; ++y) {
        int x1 = top_left.x + static_cast<int>((y - top_left.y) * left_slope);
        int x2 = top_right.x + static_cast<int>((y - top_right.y) * right_slope);
        std::cout << "Drawing line from (" << x1 << ", " << y << ") to (" << x2 << ", " << y << ")" << std::endl;
        SDL_RenderDrawLine(renderer, x1, y, x2, y);
    }
}

void render::renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz){
    SDL_RenderDrawLine(renderer, trapz.top_left.x, trapz.top_left.y, trapz.top_right.x, trapz.top_right.y);
    SDL_RenderDrawLine(renderer, trapz.top_right.x, trapz.top_right.y, trapz.bottom_right.x, trapz.bottom_right.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_right.x, trapz.bottom_right.y, trapz.bottom_left.x, trapz.bottom_left.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_left.x, trapz.bottom_left.y, trapz.top_left.x, trapz.top_left.y);
}

// Function to draw a horizontal line
void test::drawHorizontalLine(SDL_Renderer* renderer, int x1, int x2, int y) {
    if (x1 > x2) { 
        int temp = x1; 
        x1 = x2; 
        x2 = temp; 
    }
    SDL_RenderDrawLine(renderer, x1, y, x2, y);
}

// Linear interpolation helper
float test::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

void test::drawFilledTrapeziumScanline(SDL_Renderer* renderer, Trapezium* trapezium) {
    int yStart = trapezium->top_left.y;
    int yEnd = trapezium->bottom_left.y;

    for (int y = yStart; y <= yEnd; y++) {
        float tTop = (float)(y - trapezium->top_left.y) / (trapezium->bottom_left.y - trapezium->top_left.y);
        float tBottom = (float)(y - trapezium->top_right.y) / (trapezium->bottom_right.y - trapezium->top_right.y);

        int xLeft = (int)lerp(trapezium->top_left.x, trapezium->bottom_left.x, tTop);
        int xRight = (int)lerp(trapezium->top_right.x, trapezium->bottom_right.x, tBottom);

        drawHorizontalLine(renderer, xLeft, xRight, y);
    }
}

// Method 2: Pixel-by-pixel filling
void test::drawFilledTrapeziumPixel(SDL_Renderer* renderer, Trapezium* trapezium) {
    int minX = SDL_min(SDL_min(trapezium->top_left.x, trapezium->top_right.x), SDL_min(trapezium->bottom_left.x, trapezium->bottom_right.x));
    int maxX = SDL_max(SDL_max(trapezium->top_left.x, trapezium->top_right.x), SDL_max(trapezium->bottom_left.x, trapezium->bottom_right.x));
    int minY = SDL_min(SDL_min(trapezium->top_left.y, trapezium->top_right.y), SDL_min(trapezium->bottom_left.y, trapezium->bottom_right.y));
    int maxY = SDL_max(SDL_max(trapezium->top_left.y, trapezium->top_right.y), SDL_max(trapezium->bottom_left.y, trapezium->bottom_right.y));

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (isPointInTrapezium(x, y, trapezium)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

// Helper function to check if a point is inside the trapezium
int test::isPointInTrapezium(int px, int py, Trapezium* trapezium) {
    return isPointInTriangle(px, py, 
                             trapezium->top_left.x, trapezium->top_left.y, 
                             trapezium->top_right.x, trapezium->top_right.y, 
                             trapezium->bottom_left.x, trapezium->bottom_left.y) 
           || 
           isPointInTriangle(px, py, 
                             trapezium->top_right.x, trapezium->top_right.y, 
                             trapezium->bottom_right.x, trapezium->bottom_right.y, 
                             trapezium->bottom_left.x, trapezium->bottom_left.y);
}

// Helper function to check if a point is inside a triangle
int test::isPointInTriangle(int px, int py, int x1, int y1, int x2, int y2, int x3, int y3) {
    int d1 = (px - x2) * (y1 - y2) - (x1 - x2) * (py - y2);
    int d2 = (px - x3) * (y2 - y3) - (x2 - x3) * (py - y3);
    int d3 = (px - x1) * (y3 - y1) - (x3 - x1) * (py - y1);

    int has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    int has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}