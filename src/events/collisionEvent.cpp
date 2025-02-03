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

void CollisionHandler::handleCollision(CollisionEvent& e){
    static auto lastCollisionType = EventType::None;
    auto type = e.GetEventType();
    if(type == lastCollisionType){
        return;
    }
    lastCollisionType = type;
    LOG_WARNING("Not fully implemented.");
    switch(type){
        case EventType::TetrionLeftCollision:
            LOG_DEBUG("Handling Left Collision");
            break;
        case EventType::TetrionRightCollision:
            LOG_DEBUG("Handling Right Collision");
            break;
        case EventType::TetrionBottomCollision:
            LOG_DEBUG("Handling Bottom Collision");
            break;
        case EventType::TetrominoCollision:
            LOG_DEBUG("Handling Tetromino Collision");
            break;
        default:
            LOG_ERROR("Unknown Collision Event");
    }
}