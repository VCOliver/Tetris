#pragma once 

#include "pch.h"
#include "event.hpp"

class KeyEvent : public Event
{
public:
    struct Key{
        KeyCode keycode;
        bool isRepeat;
    };  
    inline Key getKey() const { return key;}
    KeyCode GetKeyCode() const { return keyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
    KeyEvent(const KeyCode keycode)
        : keyCode(keycode) {}

    KeyCode keyCode;
    Key key;
};

class KeyPressedEvent : public KeyEvent
{
public:
    KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
        : KeyEvent(keycode), isRepeat(isRepeat) {
            key = {keycode, isRepeat};
        }

    bool IsRepeat() const { return isRepeat; }

    std::string ToString() const override
    {
        char c_keycode = keyCode;
        std::stringstream ss;
        ss << "KeyPressedEvent: " << c_keycode << " (repeat = " << isRepeat << ")";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
private:
    bool isRepeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
    KeyReleasedEvent(const KeyCode keycode)
        : KeyEvent(keycode) {
            key = {keycode};
        }

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};
