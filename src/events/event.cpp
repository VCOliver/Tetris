#include "events/event.hpp"
#include "events/keyEvent.hpp"
#include "events/windowEvent.hpp"

std::unique_ptr<Event> TranslateSDLEvent(const SDL_Event& sdlEvent)
{
    switch (sdlEvent.type)
    {
        case SDL_QUIT:
            return std::make_unique<WindowCloseEvent>();
        case SDL_KEYUP:
            return std::make_unique<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
        case SDL_KEYDOWN:
            return std::make_unique<KeyPressedEvent>(sdlEvent.key.keysym.sym, sdlEvent.key.repeat);
        case SDL_WINDOWEVENT:
            {
                auto window = sdlEvent.window;
                switch (window.event) {
                    case SDL_WINDOWEVENT_SHOWN:
                        std::cout << "Window shown!" << std::endl;
                        return nullptr;
                    case SDL_WINDOWEVENT_RESIZED:
                        return std::make_unique<WindowResizeEvent>(window.data1, window.data2);
                    default:
                        return nullptr;
                }
            }
            break;
        // Handle other SDL2 event types here
        default:
            return nullptr;
    }
}