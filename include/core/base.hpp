#pragma once

#define BIT(x) (1 << x)

#define KeyCode SDL_Keycode

// Block defines
#define STD_BLOCK_W 20
#define STD_BLOCK_H 20 
#define STD_LINE_THICKNESS 2

// Tetrion defines
#define TETRION_H 24
#define TETRION_W 12

// Window defines
#define STD_WINDOW_WIDTH 800
#define STD_WINDOW_HEIGHT 600
#define WINDOW_FLAGS (SDL_WINDOW_RESIZABLE| SDL_WINDOW_HIDDEN)

// Renderer defines
#define RENDER_FLAGS (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)

constexpr char fontPath[] = "assets/fonts/Minecraftia-Regular.ttf";

#define TERMINATE_GAME(status) this->close(); exit(status);