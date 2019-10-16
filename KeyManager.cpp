#include "KeyManager.h"

void KeyManager::setKey(cocos2d::EventKeyboard::KeyCode key) {
    if(!isKeyPressed(key)) {
        pressedKeys[key] = std::chrono::system_clock::now();
    }
}

void KeyManager::removeKey(cocos2d::EventKeyboard::KeyCode key) {
    pressedKeys.erase(key);
}

double KeyManager::getPressedKeyTime(cocos2d::EventKeyboard::KeyCode key) {
    if(isKeyPressed(key)) {
        std::chrono::system_clock::time_point pressedTime = pressedKeys[key];
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - pressedTime).count();

    }
    return 0.0;
}

bool KeyManager::isKeyPressed(cocos2d::EventKeyboard::KeyCode key) const {
    return (pressedKeys.find(key) != pressedKeys.end());
}

