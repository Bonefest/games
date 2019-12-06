#include "GameConfiguration.h"
#include <fstream>
#include <string>


EventKeyboard::KeyCode GameConfiguration::MOVE_LEFT;
EventKeyboard::KeyCode GameConfiguration::MOVE_UP;
EventKeyboard::KeyCode GameConfiguration::MOVE_RIGHT;
EventKeyboard::KeyCode GameConfiguration::MOVE_DOWN;
EventKeyboard::KeyCode GameConfiguration::ACTIVATE_SKILL_1;
EventKeyboard::KeyCode GameConfiguration::ACTIVATE_SKILL_2;
EventKeyboard::KeyCode GameConfiguration::ACTIVATE_SKILL_3;
EventKeyboard::KeyCode GameConfiguration::USE;

cocos2d::Animation* GameConfiguration::animationHumanUp;
cocos2d::Animation* GameConfiguration::animationHumanDown;
cocos2d::Animation* GameConfiguration::animationHumanLeft;
cocos2d::Animation* GameConfiguration::animationHumanRight;

int GameConfiguration::MAX_STATE_QUEUE_SIZE = 10;


void GameConfiguration::loadGameConfiguration(const char* fileName) {
    nlohmann::json parser;
    std::ifstream settingsFile(fileName);
    if(settingsFile.is_open()) {
        settingsFile >> parser;
        loadKeys(parser);//    animationHumanUp = cocos2d::Animation::create();
//    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("01.png"));
//    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("02.png"));
//    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("03.png"));
//    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("04.png"));
//    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("05.png"));
//    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("00.png"));

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
    std::string humanAnimation = parser["animations"]["human"];

    cache->addSpriteFramesWithFile("human.plist");
    animationHumanUp = cocos2d::Animation::create();
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("01.png"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("02.png"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("03.png"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("04.png"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("05.png"));
    animationHumanUp->addSpriteFrame(cache->getSpriteFrameByName("00.png"));
    animationHumanUp->setDelayPerUnit(0.15f);
    animationHumanUp->setLoops(-1);
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
