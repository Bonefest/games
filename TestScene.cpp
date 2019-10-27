#include "TestScene.h"
#include "MainScene.h"

bool TestScene::init() {
    if(!cocos2d::Scene::init()) {
        return false;
    }
    initListeners();

    _debugDrawer = cocos2d::DrawNode::create();
    activateDebug(true);
    addChild(_debugDrawer);

    _backButton = cocos2d::ui::Button::create();

    cocos2d::Vec2 buttonPosition = cocos2d::Director::getInstance()->getVisibleSize();
    buttonPosition.x *= 0.8f;
    buttonPosition.y *= 0.2f;

    _backButton->setTitleText("Back");
    _backButton->setTitleFontSize(26.0f);
    _backButton->setPosition(buttonPosition);
    _backButton->addTouchEventListener(CC_CALLBACK_1(TestScene::backButtonCallback,this));
    addChild(_backButton);

    return true;
}

void TestScene::initListeners() {
    cocos2d::EventListenerMouse* mouseListener = cocos2d::EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(TestScene::onMouseMove, this);
    mouseListener->onMouseDown = CC_CALLBACK_1(TestScene::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(TestScene::onMouseUp, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

}

void TestScene::backButtonCallback(cocos2d::Ref* psender) {
    cocos2d::Director::getInstance()->replaceScene(MainScene::createScene());
}

void TestScene::drawChildBoundingBoxes() {
    cocos2d::Vector<cocos2d::Node*>& childrens = getChildren();
    cocos2d::Rect childRect;

    for(auto child : childrens) {
        childRect = child->getBoundingBox();
        _debugDrawer->drawRect(cocos2d::Vec2(childRect.getMinX(),childRect.getMinY()),
                              cocos2d::Vec2(childRect.getMaxX(),childRect.getMaxY()),
                              cocos2d::Color4F::RED);
    }

}


void TestScene::activateDebug(bool activate) {
    drawingBoundingBoxes = activate;
    _debugDrawer->clear();
}
