#ifndef KEYMANAGER_H_INCLUDED
#define KEYMANAGER_H_INCLUDED

#include "cocos2d.h"

#include <map>
#include <chrono>

class KeyManager {
public:
    void setKey(cocos2d::EventKeyboard::KeyCode key);
    void removeKey(cocos2d::EventKeyboard::KeyCode key);

    bool isKeyPressed(cocos2d::EventKeyboard::KeyCode key) const;
    double getPressedKeyTime(cocos2d::EventKeyboard::KeyCode key);

private:
    std::map<cocos2d::EventKeyboard::KeyCode,std::chrono::system_clock::time_point> pressedKeys;
};

#endif // KEYMANAGER_H_INCLUDED
