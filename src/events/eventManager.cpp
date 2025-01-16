#include "events/eventManager.hpp"

void EventManager::addListener(EventType type, EventManager::callback_t callback){
    eventListeners[type].push_back(callback);
}

void EventManager::NotifyAll(){

    EventType eventType = static_cast<EventType>(event.type);

    auto it = eventListeners.find(eventType);
    if (it != eventListeners.end()) {
        for (const auto& callback : it->second) {
            callback(event);
        }
    }

}

void EventManager::handleEvents(){
    while(SDL_PollEvent(&event)){
        NotifyAll();
    }
}