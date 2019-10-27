#include "SlingshotScene.h"

SlingshotScene* SlingshotScene::createScene() {
    return create();
}

bool SlingshotScene::init() {
    if(!TestScene::init()) {
        cocos2d::log("Unable to initialize the SlingshotScene!\n");
        return false;
    }
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

    clicked = false;
    lastClickPosition = cursorPosition = cocos2d::Vec2::ZERO;

    cocos2d::Node* box = cocos2d::Sprite::create("HelloWorld.png");
    box->setContentSize(cocos2d::Size(32,32));
    box->setPosition(visibleSize/2);
    component = PhysicsComponent::createComponent();
    box->addComponent(component);

    addChild(box);
    scheduleUpdate();
    return true;
}

void SlingshotScene::update(float delta) {
    _debugDrawer->clear();
    if(drawingBoundingBoxes) {
        drawChildBoundingBoxes();
    }

    if(clicked) {
        _debugDrawer->drawPoint(cocos2d::Vec2(lastClickPosition), 5.0f, cocos2d::Color4F::BLUE);
        _debugDrawer->drawLine(cursorPosition, lastClickPosition, cocos2d::Color4F::RED);
        drawTrajectory(lastClickPosition - cursorPosition, lastClickPosition, TRAJECTORY_STEP);
    }


}

void SlingshotScene::drawTrajectory(const cocos2d::Vec2& initialVelocity, const cocos2d::Vec2& initialPosition, float timeStep, const cocos2d::Color4F& color) {
    cocos2d::Vec2 pointPosition;
    for(float time = 0.0f;;time += timeStep) {
        _debugDrawer->drawLine(initialPosition + initialVelocity*time + DEFAULT_GRAVITY*time*time*0.5f,
                              initialPosition + initialVelocity*(time + timeStep) + DEFAULT_GRAVITY*(time + timeStep)*(time + timeStep)*0.5f,
                              color);
        if(initialPosition.y + initialVelocity.y*time + DEFAULT_GRAVITY.y*time*time*0.5f <= 0.0f) break;
    }
}

void SlingshotScene::onMouseMove(cocos2d::EventMouse* event) {
    cursorPosition = event->getLocation();
    cursorPosition.y = visibleSize.height - cursorPosition.y;
}

void SlingshotScene::onMouseDown(cocos2d::EventMouse* event) {
    lastClickPosition = event->getLocation();
    lastClickPosition.y = visibleSize.height - lastClickPosition.y;

    clicked = true;
}


void SlingshotScene::onMouseUp(cocos2d::EventMouse* event) {
    component->setVelocity(lastClickPosition - cursorPosition);
    component->getOwner()->setPosition(lastClickPosition);

    clicked = false;
}
