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

    return true;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
