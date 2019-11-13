#include "MainScene.h"

#include "SlingshotScene.h"
#include "ParticleScene.h"
#include "DiamondSquareScene.h"
#include "OrbitalScene.h"

MainScene* MainScene::createScene() {
    return create();
}

bool MainScene::init() {
    if(!cocos2d::Scene::init()) {
        cocos2d::log("Unable to initialize the MainScene!\n");
        return false;
    }

    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    initMenu();

    return true;
}


void MainScene::initMenu() {
    menu = cocos2d::Menu::create();
    addScene("Slingshot", SlingshotScene::createScene, 1);
    addScene("Particles", ParticleScene::createScene, 2);
    addScene("Diamond Square", DiamondSquareScene::createScene, 3);
    addScene("Oribtals", OrbitalScene::createScene, 4);

    menu->alignItemsVertically();
    addChild(menu);
}

void MainScene::addScene(const std::string& sceneName, std::function<TestScene*()> createFunc, unsigned int order) {
    cocos2d::MenuItemLabel* sceneLabel = cocos2d::MenuItemLabel::create(cocos2d::Label::createWithTTF(sceneName, std::string("fonts/arial.ttf"), 26),
                                                                        [=](cocos2d::Ref* ref){
                                                                            cocos2d::Director::getInstance()->replaceScene(createFunc());
                                                                        });

    menu->addChild(sceneLabel, order);
}
