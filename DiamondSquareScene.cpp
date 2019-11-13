#include "DiamondSquareScene.h"

DiamondSquareScene* DiamondSquareScene::createScene() {
    return DiamondSquareScene::create();
}

bool DiamondSquareScene::init() {
    if(!TestScene::init())
        return false;

    mapDrawer = cocos2d::DrawNode::create();
    addChild(mapDrawer);

    generator.setSize(513);
    generator.generate(32);
    drawMap();

    cocos2d::EventListenerKeyboard* klistener = cocos2d::EventListenerKeyboard::create();
    klistener->onKeyPressed = CC_CALLBACK_2(DiamondSquareScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(klistener, this);

    return true;
}

void DiamondSquareScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
    if(key == cocos2d::EventKeyboard::KeyCode::KEY_R) {
        generator.generate(time(0));
        drawMap();
    }
}

void DiamondSquareScene::drawMap() {
    mapDrawer->clear();
    uint32_t mapSize = generator.getSize();
    auto mp = generator.getData();
    gaussSmooth(mp,0.84089);
    //smoothData(mp);
    //smoothData(mp);
    //smoothData(mp);
    //smoothData(mp);
    for(uint32_t y = 0;y < mapSize;++y) {
        for(uint32_t x = 0;x < mapSize;++x) {
            mapDrawer->drawPoint(cocos2d::Vec2(100 + x, 100 + y),1.0f, getColor(mp[y][x]));
        }
    }
}


cocos2d::Color4F DiamondSquareScene::getColor(double height) {
    if(height < 155.0f) {
        return cocos2d::Color4F(0.0f,0.0f,height/155.0f,1.0f);
    } else if(height >= 155.0f && height < 157.0f) {
        return cocos2d::Color4F::YELLOW;
    } else if(height >= 157.0f && height < 177.0f) {
        return cocos2d::Color4F(0.5f,1.0f,0.0f,1.0f);
    } else if(height >= 177.0f && height < 187.0f) {
        return cocos2d::Color4F(0.2f,1.0f,0.0f,1.0f);
    } else if(height >= 187.0f && height < 197.0f) {
        return cocos2d::Color4F::GREEN;
    } else if(height >= 197.0f && height < 207.0f) {
        return cocos2d::Color4F(0.58f,0.58f,0.58f,1.0f);
    } else if(height >= 207.0f && height < 217.0f) {
        return cocos2d::Color4F(0.65f,0.65f,0.65f,1.0f);
    } else if(height >= 217.0f && height < 237.0f) {
        return cocos2d::Color4F(0.8f,0.8f,0.8f,1.0f);
    }
    return cocos2d::Color4F(1.0f,1.0f,1.0f,1.0f);
}
