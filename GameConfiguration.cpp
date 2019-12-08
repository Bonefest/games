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

cocos2d::SpriteFrameCache* GameConfiguration::cache;

int GameConfiguration::MAX_STATE_QUEUE_SIZE = 10;


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
    cache = cocos2d::SpriteFrameCache::getInstance();
    std::string humanAnimation = parser["animation_lists"]["human"];

    cache->addSpriteFramesWithFile(humanAnimation);
    animationHumanUp = loadAnimation(parser, parser["animations"]["human"]["up"],"human");
    animationHumanUp->retain();
    animationHumanDown = loadAnimation(parser, parser["animations"]["human"]["down"],"human");
    animationHumanDown->retain();
    animationHumanLeft = loadAnimation(parser, parser["animations"]["human"]["left"],"human");
    animationHumanLeft->retain();
    animationHumanRight = loadAnimation(parser, parser["animations"]["human"]["right"],"human");
    animationHumanRight->retain();
}


cocos2d::Animation* GameConfiguration::loadAnimation(nlohmann::json& parser,const std::vector<std::string>& frames, const std::string& animationName) {
    cocos2d::Animation* animation = cocos2d::Animation::create();
    for(const std::string& frame: frames) {
        animation->addSpriteFrame(cache->getSpriteFrameByName(frame));
        animation->setDelayPerUnit(parser["animations"][animationName].value("delay", 0.18));
        animation->setLoops(-1);
    }

    return animation;
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
