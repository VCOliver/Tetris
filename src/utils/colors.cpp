#include "utils/colors.hpp"

SDL_Color Color::toSDL_Color(){
    return {red, green, blue, 255};
}