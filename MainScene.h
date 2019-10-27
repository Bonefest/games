#ifndef _MAINSCENE_H_
#define _MAINSCENE_H_

#include "cocos2d.h"
#include "../cocoslib/KeyManager.h"
#include "TestScene.h"

USING_NS_CC;

typedef TestScene*(*createSceneCallback)();

class MainScene : public TestScene {
public:
    CREATE_FUNC(MainScene);
    static MainScene* createScene();
    bool init();
    void initMenu();

private:
    void addScene(const std::string& sceneName, std::function<TestScene*()> createFunc, unsigned int order);

    cocos2d::Size visibleSize;
    cocos2d::Menu* menu;

    std::map<std::string,std::function<TestScene*()>> callbacks;
};

#endif // _MAINSCENE_H_
