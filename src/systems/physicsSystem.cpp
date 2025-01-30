#include "systems/physicsSystem.hpp"

void PhysicsSystem::update(){
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
    cout << "Difficulty increased! New gravity speed: " 
            << this->getGravitySpeed().count() << "ms\n";
}

