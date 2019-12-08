#include "GameScene.h"
#include "GameConfiguration.h"
#include "Game.h"
#include "State.h"
#include "Entity.h"

GameScene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if(!Scene::init()) {
        log("[Error] Unable to initialize a game scene!");
        return false;
    }

    GameConfiguration::loadGameConfiguration("settings.json");

    initListeners();
    Entity* entity = Entity::createEntity();
    entity->setAnimation(UP, GameConfiguration::animationHumanUp);
    entity->setAnimation(DOWN, GameConfiguration::animationHumanDown);
    entity->setAnimation(LEFT, GameConfiguration::animationHumanLeft);
    entity->setAnimation(RIGHT, GameConfiguration::animationHumanRight);

    entity->setPosition(cocos2d::Vec2(300,300));
    entity->addNewState(std::make_shared<StandingState>());
    Game::getInstance()->setPlayer(entity);

    addChild(entity);

    scheduleUpdate();
    log("[Success] Game scene has been initialized!");
    return true;
}

bool GameScene::initListeners() {
    EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
    if(!keyboardListener) return false;

    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    return true;
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event) {
    inputHandler.onKeyPressed(key);
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode key, Event* event) {
    inputHandler.onKeyReleased(key);
}

void GameScene::update(float delta) {
    Game::getInstance()->getPlayer()->update(delta);
}
