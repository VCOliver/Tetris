#include "events/collisionEvent.hpp"

#include "core/log.hpp"

void CollisionChecker::pushEvent(EventType type){
    SDL_Event event;
    SDL_zero(event);
    event.type = COLLISION_EVENT;
    event.user.code = static_cast<Sint32>(type);
    SDL_PushEvent(&event);
}

void CollisionChecker::checkCollision(){
    auto occupied = tetromino.getOccupiedPositions();
    auto min_X_pos = tetrion.getStartPosition().x+1;
    auto max_X_pos = tetrion.getLastPosition().x-1;
    auto max_Y_pos = tetrion.getLastPosition().y-1;
    for(auto& pos : occupied){
        if(pos.x == min_X_pos){
            pushEvent(EventType::TetrionLeftCollision);
            break;
        }
        if(pos.x == max_X_pos){
            pushEvent(EventType::TetrionRightCollision);
            break;
        }
        if(pos.y == max_Y_pos){
            pushEvent(EventType::TetrionBottomCollision);
            break;
        }
    }    
}

InputManager* CollisionHandler::m_inputManager = nullptr;
PhysicsSystem* CollisionHandler::m_physicsSystem = nullptr;

void CollisionHandler::handleCollision(CollisionEvent& e){
    static auto prev = EventType::None;
    if(prev != e.GetEventType()) LOG_WARNING("Collision handling not fully implemented.");

    auto type = e.GetEventType();
    prev = type;

    auto keys = m_inputManager->getKeyCommands();
    switch(type){
        case EventType::TetrionLeftCollision:
            m_inputManager->blockKey(keys.LEFT.first);
            break;
        case EventType::TetrionRightCollision:
            m_inputManager->blockKey(keys.RIGHT.first);
            break;
        case EventType::TetrionBottomCollision:
            m_inputManager->blockKey(keys.DOWN.first);
            m_physicsSystem->stopGravity();
            break;
        case EventType::TetrominoCollision:
            break;
        default:
            LOG_ERROR("Unknown Collision Event");
    }
}