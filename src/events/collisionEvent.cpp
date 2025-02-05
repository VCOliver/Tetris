#include "events/collisionEvent.hpp"

#include "core/log.hpp"
#include "events/TetrominoEvent.hpp"


void CollisionChecker::checkCollision(){
    auto occupied = tetromino.getOccupiedPositions();
    auto min_X_pos = tetrion.getStartPosition().x+1;
    auto max_X_pos = tetrion.getLastPosition().x-1;
    auto max_Y_pos = tetrion.getLastPosition().y-1;
    for(auto& pos : occupied){
        if(pos.x == min_X_pos){
            Event::pushEvent(COLLISION_EVENT, EventType::TetrionLeftCollision);
            break;
        }
        if(pos.x == max_X_pos){
            Event::pushEvent(COLLISION_EVENT, EventType::TetrionRightCollision);
            break;
        }
        if(pos.y == max_Y_pos){
            Event::pushEvent(COLLISION_EVENT, EventType::TetrionBottomCollision);
            break;
        }
    }    
}

InputManager* CollisionHandler::m_inputManager = nullptr;
PhysicsSystem* CollisionHandler::m_physicsSystem = nullptr;

void CollisionHandler::handleCollision(CollisionEvent& e){
    static auto prev = EventType::None;
    if(prev != e.GetEventType()) {
        LOG_DEBUG("Collision Event: ", e.GetName());
        LOG_WARNING("Collision handling not fully implemented.");
    }

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
            Event::pushEvent(TETROMINO_EVENT, EventType::TetrominoDroped);
            break;
        case EventType::TetrominoCollision:
            break;
        default:
            LOG_ERROR("Unknown Collision Event");
    }
}