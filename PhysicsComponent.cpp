#include "PhysicsComponent.h"

PhysicsComponent* PhysicsComponent::createComponent() {
    return PhysicsComponent::create();
}

bool PhysicsComponent::init() {
    if(!cocos2d::Component::init()) {
        cocos2d::log("Unable to initialize a physics component!");
    }


    gravityEnabled = true;
    gravity = DEFAULT_GRAVITY;
    velocity = cocos2d::Vec2::ZERO;
    acceleration = cocos2d::Vec2::ZERO;

    return true;
}

void PhysicsComponent::update(float delta) {
    if(!isEnabled()) return;

    if(isGravityEnabled()) {
        velocity += delta*gravity;
    }

    cocos2d::Vec2 ownerPosition = getOwner()->getPosition();
    ownerPosition += delta*velocity;

    getOwner()->setPosition(ownerPosition);
}

void PhysicsComponent::setVelocity(const cocos2d::Vec2& velocity) {
    this->velocity = velocity;
}
