#include "events/event.hpp"
#include "events/keyEvent.hpp"
#include "events/windowEvent.hpp"

std::unique_ptr<Event> TranslateSDLEvent(const SDL_Event& sdlEvent)
{
    switch (sdlEvent.type)
    {
        case SDL_KEYDOWN:
            return std::make_unique<KeyPressedEvent>(sdlEvent.key.keysym.sym);
        case SDL_QUIT:
            return std::make_unique<WindowCloseEvent>();
        // Handle other SDL2 event types here
        default:
            return nullptr;
    }
}