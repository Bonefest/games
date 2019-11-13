#include "OrbitalScene.h"

OrbitalScene* OrbitalScene::createScene() {
    return OrbitalScene::create();
}

bool OrbitalScene::init() {
    if(!TestScene::init())
        return false;

    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    initEventListeners();

    drawer = cocos2d::DrawNode::create();
    addChild(drawer);

    initPlanets();

    scheduleUpdate();
    return true;
}

void OrbitalScene::initEventListeners() {
    cocos2d::EventListenerMouse* mlistener = cocos2d::EventListenerMouse::create();
    mlistener->onMouseDown = CC_CALLBACK_1(OrbitalScene::onMouseDown, this);
    mlistener->onMouseMove = CC_CALLBACK_1(OrbitalScene::onMouseMove, this);
    mlistener->onMouseUp = CC_CALLBACK_1(OrbitalScene::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mlistener, this);
}

void OrbitalScene::initPlanets() {
    planetOne = cocos2d::Node::create();
    planetOne->setPosition(visibleSize/4);
    componentOne = PhysicsComponent::createComponent();
    componentOne->setMass(30.0f);
    componentOne->setGravityEnabled(false);
    planetOne->addComponent(componentOne);
    addChild(planetOne);

    planetTwo = cocos2d::Node::create();
    planetTwo->setPosition(visibleSize/2.0);
    componentTwo = PhysicsComponent::createComponent();
    componentTwo->setMass(10000.0f);
    componentTwo->setGravityEnabled(false);
    planetTwo->addComponent(componentTwo);
    addChild(planetTwo);

}

void OrbitalScene::update(float delta) {
    drawNodes();
    calculatePhysics(delta);
}

void OrbitalScene::drawNodes() {
    drawer->clear();
    drawer->drawCircle(planetOne->getPosition(), 10.0f, 1.0f, 12, false, cocos2d::Color4F::RED);
    drawer->drawCircle(planetTwo->getPosition(), 20.0f, 1.0f, 12, false, cocos2d::Color4F::GREEN);
    drawer->drawPoint(planetOne->getPosition(), 5.0f, cocos2d::Color4F::BLUE);
    drawer->drawPoint(planetTwo->getPosition(), 5.0f, cocos2d::Color4F::BLUE);
    //drawer->drawLine(planetOne->getPosition(), planetTwo->getPosition(), cocos2d::Color4F::WHITE);

}

void OrbitalScene::calculatePhysics(float delta) {
    cocos2d::log("%f %f\n",planetOne->getPosition().x,planetOne->getPosition().y);

    cocos2d::Vec2 planetVelocity = componentOne->getVelocity();
    cocos2d::Vec2 direction = (planetTwo->getPosition() - planetOne->getPosition()).getNormalized();

    float planetDistance = (planetTwo->getPosition() - planetOne->getPosition()).getLength();

    float G = 4800.0f;

    float a = (G*componentTwo->getMass())/(planetDistance*planetDistance);

    cocos2d::Vec2 tangentVelocity = (std::sqrt(a*planetDistance) + 1000.0f)*direction.getPerp();

    //planetVelocity = planetVelocity + tangentVelocity + direction*a*delta;
    planetVelocity = a*delta*direction + tangentVelocity;
    componentOne->setVelocity(planetVelocity);
}

void OrbitalScene::onMouseDown(cocos2d::EventMouse* event) {
    keyManager.setMousebutton(event->getMouseButton());
}

void OrbitalScene::onMouseUp(cocos2d::EventMouse* event) {
    keyManager.removeMouseButton(event->getMouseButton());
}

void OrbitalScene::onMouseMove(cocos2d::EventMouse* event) {
    if(keyManager.isMousebuttonPressed(cocos2d::EventMouse::MouseButton::BUTTON_LEFT)) {

        planetTwo->setPosition(cocos2d::Vec2(event->getCursorX(),event->getCursorY()));
    }
}
