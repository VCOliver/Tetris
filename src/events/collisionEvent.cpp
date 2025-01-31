#include "events/collisionEvent.hpp"

#include "core/log.hpp"

void CollisionChecker::checkCollision(){
    auto occupied = tetromino.getOccupiedPositions();
    auto min_X_pos = tetrion.getStartPosition().x+1;
    auto max_X_pos = tetrion.getLastPosition().x-1;
    auto max_Y_pos = tetrion.getLastPosition().y-1;
    for(auto& pos : occupied){
        if(pos.x == min_X_pos){
            LOG_DEBUG("Collision detected on the Left side");
            SDL_Event event;
            event.type = COLLISION_EVENT;
            event.user.code = static_cast<Sint32>(EventType::TetrionLeftCollision);
            SDL_PushEvent(&event);
            return;
        }
        if(pos.x == max_X_pos){
            LOG_DEBUG("Collision detected on the Right side");
            SDL_Event event;
            event.type = COLLISION_EVENT;
            event.user.code = static_cast<Sint32>(EventType::TetrionRightCollision);
            SDL_PushEvent(&event);
            return;
        }
        if(pos.y == max_Y_pos){
            LOG_DEBUG("Collision detected on the Bottom side");
            SDL_Event event;
            event.type = COLLISION_EVENT;
            event.user.code = static_cast<Sint32>(EventType::TetrionBottomCollision);
            SDL_PushEvent(&event);
            return;
        }
    }    
}

