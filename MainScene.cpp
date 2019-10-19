#include "MainScene.h"

Scene* MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init() {

    if(!cocos2d::Scene::init()) {
        cocos2d::log("Unable to initialize scene!");
        return false;
    }

    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    tubeManager.setScene(this);

    this->runAction(cocos2d::RepeatForever::create(cocos2d::Sequence::create(cocos2d::CallFunc::create(CC_CALLBACK_0(TubeManager::generateTubePair, &tubeManager)),
                                                                             cocos2d::DelayTime::create(2.0f), nullptr )));

    initEventListeners();
    initGameObjects();

    scheduleUpdate();
    return true;
}

void MainScene::initEventListeners() {
    cocos2d::EventListenerTouchOneByOne* touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void MainScene::initGameObjects() {

    cocos2d::SpriteFrameCache* spriteCache = cocos2d::SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("FlappyList.plist");

    cocos2d::Sprite* background = cocos2d::Sprite::createWithSpriteFrameName("background-day.png");
    background->setPosition(visibleSize/2);
    addChild(background,-3);

    for(int i = 0;i<2;++i) {
        groundSprites[i] = cocos2d::Sprite::create("base.png");
        groundSprites[i]->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
        groundSprites[i]->setPositionX(i*(groundSprites[i]->getContentSize().width));
        addChild(groundSprites[i],-2,BASE_GROUND_TAG);
    }

    cocos2d::Animation* playerAnimation = cocos2d::Animation::create();
    playerAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("redbird-upflap.png"));
    playerAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("redbird-midflap.png"));
    playerAnimation->addSpriteFrame(spriteCache->getSpriteFrameByName("redbird-downflap.png"));
    playerAnimation->setDelayPerUnit(0.15f);
    playerAnimation->setLoops(-1);
    playerAnimation->setRestoreOriginalFrame(true);

    player = Player::createPlayer();
    player->setTag(PLAYER_TAG);
    player->setPosition(visibleSize/2);
    player->runAction(cocos2d::Animate::create(playerAnimation));
    player->scheduleUpdate();

    addChild(player);

}

void MainScene::update(float delta) {
    tubeManager.update(delta);
    updateGround(delta);

}

void MainScene::updateGround(float delta) {
    for(int i = 0;i<2;++i) {
        groundSprites[i]->setPositionX(groundSprites[i]->getPositionX() - GROUND_SPEED*delta);
        if(groundSprites[i]->getPositionX() <= -groundSprites[i]->getContentSize().width) {
            //Эта позиция берется из простой формулы: Ширина_объекта - значение_выхода_за_пределы =>
            //contentSize_width - (contentSize_width - posX) => 2*contentSize_width + posX
            groundSprites[i]->setPositionX(2*groundSprites[i]->getContentSize().width + groundSprites[i]->getPositionX());
        }
    }
}


bool MainScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    player->force();
    return true;
}
