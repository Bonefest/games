#ifndef GAMECONFIGURATION_H_INCLUDED
#define GAMECONFIGURATION_H_INCLUDED

#include "cocos2d.h"
#include "../cocoslib/json.hpp"

USING_NS_CC;

class GameConfiguration {
public:
    static void loadGameConfiguration(const char* fileName);

    static EventKeyboard::KeyCode MOVE_LEFT;
    static EventKeyboard::KeyCode MOVE_UP;
    static EventKeyboard::KeyCode MOVE_RIGHT;
    static EventKeyboard::KeyCode MOVE_DOWN;
    static EventKeyboard::KeyCode ACTIVATE_SKILL_1;
    static EventKeyboard::KeyCode ACTIVATE_SKILL_2;
    static EventKeyboard::KeyCode ACTIVATE_SKILL_3;
    static EventKeyboard::KeyCode USE;

    static cocos2d::Animation* animationHumanUp;
    static cocos2d::Animation* animationHumanDown;
    static cocos2d::Animation* animationHumanLeft;
    static cocos2d::Animation* animationHumanRight;

private:
    static void loadKeys(nlohmann::json& parser);
    static void loadAnimations(nlohmann::json& parser);

};


#endif // GAMECONFIGURATION_H_INCLUDED
