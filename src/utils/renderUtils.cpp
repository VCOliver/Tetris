#include "utils/renderUtils.hpp"
#include "utils/mathUtils.hpp"

const Position render::getWindowCenter(SDL_Window* window){
    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
    w /= 2;
    h /= 2;
    w /= STD_BLOCK_W;
    h /= STD_BLOCK_H;
    return {w, h};
}

void render::setRenderDrawColor(SDL_Renderer* renderer, Color color, rgba_t alpha){
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, alpha);
}

// Helper function to check if a point is inside the trapezium
bool render::isPointInTrapezium(int px, int py, const Trapezium& trapz) {
    SDL_Point p = {px, py};
    Triangle tri1 = {{trapz.top_left.x, trapz.top_left.y},
                     {trapz.top_right.x, trapz.top_right.y},
                     {trapz.bottom_left.x, trapz.bottom_left.y}
                    };
    Triangle tri2 = {{trapz.top_right.x, trapz.top_right.y},
                     {trapz.bottom_right.x, trapz.bottom_right.y},
                     {trapz.bottom_left.x, trapz.bottom_left.y}
                    };
    return isPointInTriangle(p, tri1) || isPointInTriangle(p, tri2);
}

bool render::isPointInTriangle(SDL_Point p, Triangle& tri) {
    int px = p.x;
    int py = p.y;

    // Calculate the barycentric coordinates of the point relative to the triangle
    int d1 = (px - tri.v2.x) * (tri.v1.y - tri.v2.y) - (tri.v1.x - tri.v2.x) * (py - tri.v2.y);
    int d2 = (px - tri.v3.x) * (tri.v2.y - tri.v3.y) - (tri.v2.x - tri.v3.x) * (py - tri.v3.y);
    int d3 = (px - tri.v1.x) * (tri.v3.y - tri.v1.y) - (tri.v3.x - tri.v1.x) * (py - tri.v1.y);

    // Determine if the point lies within the triangle
    int has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    int has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void render::renderFillTrapz(SDL_Renderer* renderer, const Trapezium& trapezium) {
    int minX = SDL_min(SDL_min(trapezium.top_left.x, trapezium.top_right.x), SDL_min(trapezium.bottom_left.x, trapezium.bottom_right.x));
    int maxX = SDL_max(SDL_max(trapezium.top_left.x, trapezium.top_right.x), SDL_max(trapezium.bottom_left.x, trapezium.bottom_right.x));
    int minY = SDL_min(SDL_min(trapezium.top_left.y, trapezium.top_right.y), SDL_min(trapezium.bottom_left.y, trapezium.bottom_right.y));
    int maxY = SDL_max(SDL_max(trapezium.top_left.y, trapezium.top_right.y), SDL_max(trapezium.bottom_left.y, trapezium.bottom_right.y));

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (isPointInTrapezium(x, y, trapezium)) {
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void render::renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz){
    SDL_RenderDrawLine(renderer, trapz.top_left.x, trapz.top_left.y, trapz.top_right.x, trapz.top_right.y);
    SDL_RenderDrawLine(renderer, trapz.top_right.x, trapz.top_right.y, trapz.bottom_right.x, trapz.bottom_right.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_right.x, trapz.bottom_right.y, trapz.bottom_left.x, trapz.bottom_left.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_left.x, trapz.bottom_left.y, trapz.top_left.x, trapz.top_left.y);
}
