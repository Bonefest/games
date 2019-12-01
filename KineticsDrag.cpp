#include "KineticsDrag.h"

KineticsDragScene* KineticsDragScene::createScene() {
    return KineticsDragScene::create();
}

bool KineticsDragScene::init() {
    if(!TestScene::init()) return false;

    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    mousePosition = clickedPosition = cocos2d::Vec2::ZERO;

    initObjects();


    scheduleUpdate();
    return true;
}

void KineticsDragScene::initObjects() {
    windBox = cocos2d::Node::create();
    windBox->setContentSize(cocos2d::Size(32, 32));
    windBox->setPosition(visibleSize / 2);

    projectile = cocos2d::Sprite::create("HelloWorld.png");
    projectile->setContentSize(cocos2d::Size(32, 32));

    projectileComponent = PhysicsComponent::createComponent();
    projectileComponent->setGravityEnabled(false);
    projectileComponent->setMass(300.0f);
    addChild(projectile);

    projectile->addComponent(projectileComponent);

    addChild(windBox);

    windEndPoint = windBox->getPosition();
}

void KineticsDragScene::update(float delta) {
    _debugDrawer->clear();
    _debugDrawer->drawSolidRect(windBox->getPosition() - cocos2d::Vec2(windBox->getContentSize()) / 2,
                                windBox->getPosition() + cocos2d::Vec2(windBox->getContentSize()) / 2,
                                cocos2d::Color4F::RED);
    _debugDrawer->drawLine(windBox->getPosition(), windEndPoint, cocos2d::Color4F::BLUE);
    if(!clickedPosition.equals(cocos2d::Vec2::ZERO)) _debugDrawer->drawLine(mousePosition, clickedPosition, cocos2d::Color4F::GREEN);
}

void KineticsDragScene::onMouseDown(cocos2d::EventMouse* event) {
    cocos2d::Rect rect = cocos2d::Rect(windBox->getPosition() - cocos2d::Vec2(windBox->getContentSize()) / 2, windBox->getContentSize());
    if(rect.containsPoint(event->getLocation())) {
        windBoxClicked = true;
    } else {
        clickedPosition = cocos2d::Vec2(event->getCursorX(), event->getCursorY());
        projectile->setPosition(clickedPosition);
    }
}

void KineticsDragScene::onMouseMove(cocos2d::EventMouse* event) {
    mousePosition = cocos2d::Vec2(event->getCursorX(), event->getCursorY());
    if(windBoxClicked) {
        windEndPoint = mousePosition;
    }
}

void KineticsDragScene::onMouseUp(cocos2d::EventMouse* event) {
    if(windBoxClicked) {
        windBoxClicked = false;
    }
    if(!clickedPosition.equals(cocos2d::Vec2::ZERO)) {
        projectileComponent->setVelocity(clickedPosition - mousePosition);
    }

    clickedPosition = cocos2d::Vec2::ZERO;
}
