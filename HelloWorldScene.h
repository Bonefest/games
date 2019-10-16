#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "KeyManager.h"
#include <map>
#include "Pawn.h"
#include "ObjectManager.h"
#include "conf.h"


class HelloWorld : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void initMeteors();
    void initPlayer();

    virtual void update(float delta);
    virtual void addChild(cocos2d::Node* node);
    virtual void removeChild(cocos2d::Node* node,bool cleanup);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event);

    void handleInput(float delta);
private:
    Player* player;

    KeyManager keyManager;

    MeteorManager meteorManager;
    CollisionManager collisionManager;

    cocos2d::Size visibleSize;
};

#endif // __HELLOWORLD_SCENE_H__
