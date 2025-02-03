#pragma once

#include "pch.h"

#include "core/base.hpp"
#include "events/keyEvent.hpp"
#include "inputMapping.hpp"

/**
 * @class InputManager
 * @brief Manages input events and key states, and interacts with an InputMapping object to map keys to actions.
 */
class InputManager {
public:
    /**
     * @enum KeyState
     * @brief Represents the state of a key.
     */
    enum KeyState {
        PRESSED,  /**< The key is currently pressed. */
        RELEASED,  /**< The key is currently released. */
        BLOCKED,
        FREE
    };

    /**
     * @brief Constructor for InputManager.
     * @param mapping A unique pointer to an InputMapping object that defines key-to-action mappings.
     * @note The constructor is explicit to prevent implicit conversions.
     */
    explicit InputManager(std::unique_ptr<InputMapping> mapping);

    /**
     * @brief Handles a KeyEvent and updates the internal state of the InputManager.
     * @param e A reference to the KeyEvent object representing the keyboard event.
     */
    void onEvent(KeyEvent& e);

    /**
     * @brief Processes input based on the key and event type.
     * @param key The key involved in the event (from KeyEvent::Key).
     * @param type The type of event (e.g., press, release).
     */
    void handleInput(KeyEvent::Key key, EventType type);

    /**
     * @brief Checks if a specific key is currently pressed.
     * @param key The key code to check (from KeyCode).
     * @return True if the key is pressed, false otherwise.
     */
    bool isKeyPressed(KeyCode key) const;

    // FOR TESTING
    /**
     * @brief Sets a new target for the InputMapping object.
     * @param tetro A reference to a Tetrominos object that will be the new target.
     * @note This method is intended for testing purposes!!
     */
    inline void setTarget(Tetrominos* tetro) {
        inputMapping->setNewTarget(tetro);
    }

    inline void blockKey(KeyCode key){
        setKeyState(key, KeyState::BLOCKED);
    }

    inline void unBlockKey(KeyCode key){
        setKeyState(key, KeyState::FREE);
    }

private:
    std::unique_ptr<InputMapping> inputMapping; /**< A unique pointer to the InputMapping object that handles key-to-action mappings. */
    std::unordered_map<KeyCode, KeyState> keyState_map; /**< A map that stores the current state of each key. */

    /**
     * @brief Updates the state of a specific key in the keyState_map.
     * @param key The key code to update (from KeyCode).
     * @param state The new state of the key (PRESSED or RELEASED).
     */
    void setKeyState(KeyCode key, KeyState state);
};