#include "ParticleScene.h"
#include "PhysicsComponent.h"

ParticleScene* ParticleScene::createScene() {
    return ParticleScene::create();
}

bool ParticleScene::init() {
    if(!TestScene::init()) {
        return false;
    }

    scheduleUpdate();
    return true;
}


void ParticleScene::update(float delta) {
    _debugDrawer->clear();
    if(keyManager.isMousebuttonPressed(cocos2d::EventMouse::MouseButton::BUTTON_LEFT)) {
        float circleRadius = getCircleRadius();
        _debugDrawer->drawCircle(pressed,circleRadius, 1.0f, 36, false, cocos2d::Color4F::RED);
    }
}

void ParticleScene::onMouseDown(cocos2d::EventMouse* event) {
    keyManager.setMousebutton(event->getMouseButton());
    pressed = event->getLocation();
    pressed.y = cocos2d::Director::getInstance()->getVisibleSize().height - pressed.y;
}

void ParticleScene::onMouseUp(cocos2d::EventMouse* event) {
    for(auto partIter = particles.begin(); partIter != particles.end(); partIter++)
        (*partIter)->removeFromParentAndCleanup(true);
    particles.clear();

    float circleRadius = getCircleRadius();

    float degreeStep = 360.0f/PARTICLE_AMOUNT;
    for(float currentDeg = 0.0f;currentDeg < 360.0f; currentDeg += degreeStep) {
        cocos2d::Sprite* particle = cocos2d::Sprite::create("HelloWorld.png");
        particle->setContentSize(cocos2d::Size(4,4));

        cocos2d::Vec2 circleDirection = circleRadius*cocos2d::Vec2(std::cos(3.1415*currentDeg/180.0f), std::sin(3.1415*currentDeg/180.0f));

        PhysicsComponent* component = PhysicsComponent::createComponent();
        component->setVelocity(10.0f*circleDirection);
        particle->addComponent(component);

        particle->setPosition(circleDirection+pressed);

        particles.push_back(particle);
        addChild(particle);
    }

    keyManager.removeMouseButton(event->getMouseButton());
}

float ParticleScene::getCircleRadius() {
    return std::min(MAXIMAL_RADIUS,0.04*keyManager.getPressedMouseTime(cocos2d::EventMouse::MouseButton::BUTTON_LEFT));
}
