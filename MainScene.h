#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED

#include "cocos2d.h"
#include "../cocoslib/KeyManager.h"
#include "Player.h"
#include "TubeManager.h"
#include "config.h"

USING_NS_CC;

class MainScene : public cocos2d::Scene {
public:

    CREATE_FUNC(MainScene);

    static Scene* createScene();

    virtual bool init();
    void initGameObjects();
    void initEventListeners();

    void update(float delta);
    void updateGround(float delta);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    TubeManager tubeManager;

    cocos2d::Sprite* groundSprites[2];
    Player* player;

    cocos2d::Size visibleSize;
};


#endif // MAINSCENE_H_INCLUDED
