#include "events/eventManager.hpp"

void EventManager::addListener(EventType type, EventManager::callback_t callback){
    eventListeners[type].push_back(callback);
}

void EventManager::handleEvents(){
    while(SDL_PollEvent(&event)){
        EventType eventType;

        switch(event.type) {
            case SDL_KEYDOWN:
                eventType = EventType::KEY_DOWN;
                break;
            case SDL_KEYUP:
                eventType = EventType::KEY_UP;
            case SDL_QUIT:
                eventType = EventType::QUIT;
                break;
            default:
                continue;
        }   

        auto it = eventListeners.find(eventType);
        if (it != eventListeners.end()) {
            for (const auto& callback : it->second) {
                get<keyboard_handler>(callback)();
            }
        }
    }
}