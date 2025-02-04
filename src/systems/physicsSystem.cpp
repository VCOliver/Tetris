#include "systems/physicsSystem.hpp"

#include "core/log.hpp"

void PhysicsSystem::update(){
    if(!gravity_enabled) return; //Prevent gravity from being applied

    auto now = std::chrono::steady_clock::now();
    if (now - lastUpdateTime >= gravityInterval) {
        activeTetromino->move(Tetrominos::DOWN);  // Apply gravity
        lastUpdateTime = now;
    }
}

void PhysicsSystem::onLevelUpEvent(){
    using namespace std;
    this->setGravitySpeed(max(
        chrono::milliseconds(100),
        this->getGravitySpeed() - chrono::milliseconds(50)
    ));
    LOG_DEBUG("Difficulty increased! New gravity speed: ", 
               this->getGravitySpeed().count(), "ms");
}

