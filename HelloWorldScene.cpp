#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <cmath>
#include "conf.h"

#include "Factory.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
    if ( !Scene::init() ) {
        return false;
    };

    meteorManager.setScene(this);

    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    initPlayer();
    initMeteors();

    auto klistener = cocos2d::EventListenerKeyboard::create();
    klistener->onKeyPressed  = CC_CALLBACK_2(HelloWorld::onKeyPressed,this);
    klistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased,this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(klistener,this);
    this->scheduleUpdate();
    return true;
}

void HelloWorld::initPlayer() {
    std::vector<cocos2d::Vec2> nodePoints(5);
    nodePoints[0] = cocos2d::Vec2(0,32.0f);
    nodePoints[1] = cocos2d::Vec2(32.0f,16.0f);
    nodePoints[2] = cocos2d::Vec2(0.0f,0.0f);
    nodePoints[3] = cocos2d::Vec2(9.0f,16.0f);
    nodePoints[4] = cocos2d::Vec2(0.0f,32.0f);

    //NEED A FACTORY
    player = Player::createPlayer(nodePoints.data(),5);
    player->setContentSize(cocos2d::Size(32,32));
    player->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
    player->setColor(cocos2d::Color4F::GREEN);
    player->setName("Player");
    this->addChild(player);

    auto playerKeyListener = cocos2d::EventListenerKeyboard::create();
    playerKeyListener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed,player);
    playerKeyListener->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased,player);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(playerKeyListener,this);
}
void HelloWorld::initMeteors() {
    Pawn* createdMeteor = nullptr;
    for(int i = 0;i<START_METEOR_COUNT;++i) {
        createdMeteor = MeteorFactory::createNewMeteor();
        createdMeteor->setPosition(cocos2d::random(0.0f,visibleSize.width),cocos2d::random(0.0f,visibleSize.height));
        meteorManager.addObject(createdMeteor);
        this->addChild(createdMeteor);
    }
}

#include <iostream>
void HelloWorld::update(float delta) {
    player->update(delta);
    meteorManager.update(delta);
    collisionManager.update(delta);

    handleInput(delta);
}

void HelloWorld::handleInput(float delta) {

    cocos2d::Vec2 speed = player->getSpeed();
    if(keyManager.isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) || keyManager.isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A)) {
        player->setRotation(player->getRotation() - ROTATING);
    } else if(keyManager.isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || keyManager.isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D)) {
        player->setRotation(player->getRotation() + ROTATING);
    }
    double angle = toRad(-player->getRotation());
    speed = speed.length()*cocos2d::Vec2(cos(angle),sin(angle));
    if(keyManager.isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) || keyManager.isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W)) {

        if(speed.length() < player->getMaximalSpeedLength())
            speed.add(delta*ACCELERATION*cocos2d::Vec2(cos(angle) ,sin(angle)));
    } else if(speed.length() > 1){
        cocos2d::Vec2 tempSpeed = speed;
        tempSpeed.add(-delta*ACCELERATION/2.0*cocos2d::Vec2(cos(angle),sin(angle)));
        if( (tempSpeed.x < 0 && speed.x >= 0) || (tempSpeed.x >= 0 && speed.x < 0) ) tempSpeed.x = 0;
        if( (tempSpeed.y < 0 && speed.y >= 0) || (tempSpeed.y >= 0 && speed.y < 0) ) tempSpeed.y = 0;
        speed = tempSpeed;
    }
    if(speed.length() < 1) speed = cocos2d::Vec2::ZERO;
    player->setSpeed(speed);
}

void HelloWorld::onKeyPressed(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event) {
    keyManager.setKey(key);
}


void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event) {
    keyManager.removeKey(key);
}


void HelloWorld::addChild(cocos2d::Node* node) {
    cocos2d::Scene::addChild(node);
    if(dynamic_cast<Pawn*>(node) != nullptr)
        collisionManager.addObject(dynamic_cast<Pawn*>(node));
}

void HelloWorld::removeChild(cocos2d::Node* node,bool cleanup) {
    cocos2d::Scene::removeChild(node,cleanup);
    if(dynamic_cast<Pawn*>(node) != nullptr)
        collisionManager.removeObject(dynamic_cast<Pawn*>(node));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
