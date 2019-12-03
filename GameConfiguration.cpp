#include "GameConfiguration.h"
#include <fstream>
#include <string>

void GameConfiguration::loadGameConfiguration(const char* fileName) {
    nlohmann::json parser;
    std::ifstream settingsFile(fileName);
    if(settingsFile.is_open()) {
        settingsFile >> parser;
        loadKeys(parser);
        loadAnimations(parser);
    }
}

void GameConfiguration::loadKeys(nlohmann::json& parser) {
    MOVE_LEFT = parser.value("Move Left", EventKeyboard::KeyCode::KEY_A);
    MOVE_UP = parser.value("Move Up", EventKeyboard::KeyCode::KEY_W);
    MOVE_RIGHT = parser.value("Move Right", EventKeyboard::KeyCode::KEY_D);
    MOVE_DOWN = parser.value("Move Down", EventKeyboard::KeyCode::KEY_S);

    ACTIVATE_SKILL_1 = parser.value("Activate skill 1", EventKeyboard::KeyCode::KEY_1);
    ACTIVATE_SKILL_2 = parser.value("Activate skill 2", EventKeyboard::KeyCode::KEY_2);
    ACTIVATE_SKILL_3 = parser.value("Activate skill 3", EventKeyboard::KeyCode::KEY_3);

    USE = parser.value("Use", EventKeyboard::KeyCode::KEY_SPACE);

}

void GameConfiguration::loadAnimations(nlohmann::json& parser) {
    cocos2d::SpriteFrameCache* cache = cocos2d::SpriteFrameCache::getInstance();
    std::string humanAnimation = parser["humanAnimation"];

    cache->addSpriteFramesWithFile(humanAnimation);
    animationHumanUp = cocos2d::Animation::create();
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("human_up_1"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("human_up_2"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("human_up_3"));
}

/*
First saving config

    nlohmann::json jest;
    jest["Move Left"] = cocos2d::EventKeyboard::KeyCode::KEY_A;
    jest["Move Up"] = cocos2d::EventKeyboard::KeyCode::KEY_W;
    jest["Move Right"] = cocos2d::EventKeyboard::KeyCode::KEY_D;
    jest["Move Down"] = cocos2d::EventKeyboard::KeyCode::KEY_S;
    jest["Activate skill 1"] = cocos2d::EventKeyboard::KeyCode::KEY_1;
    jest["Activate skill 2"] = cocos2d::EventKeyboard::KeyCode::KEY_2;
    jest["Activate skill 3"] = cocos2d::EventKeyboard::KeyCode::KEY_3;
    jest["USE"] = cocos2d::EventKeyboard::KeyCode::KEY_SPACE;

    std::ofstream ftemp("settings.json");
    ftemp << jest;
*/
