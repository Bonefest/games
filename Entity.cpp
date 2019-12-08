#include "Entity.h"
#include "GameConfiguration.h"

Entity* Entity::createEntity() {
    return Entity::create();
}

bool Entity::init() {
    if(!Sprite::init()) return false;

    speed = cocos2d::Vec2::ZERO;
    currentAnimate = nullptr;

    return true;
}

void Entity::update(float delta) {
    setPosition(getPosition() + getSpeed()*delta);
}

void Entity::runAnimation(AnimationType type) {
    auto animationIter = animations.find(type);
    if(animationIter != animations.end()) {
        stopActionByTag(CURRENT_ANIMATION_TAG);
        currentAnimate = cocos2d::Animate::create(animationIter->second);
        currentAnimate->setTag(CURRENT_ANIMATION_TAG);
        runAction(currentAnimate);
    }
    //else animationDefault
}

void Entity::setAnimation(AnimationType type, cocos2d::Animation* animation) {
    animations[type] = animation;
}

void Entity::addNewState(std::shared_ptr<EntityState> state) {
    if(!states.empty()) states.front()->onExit(this);
    states.push_front(state);
    state->onEnter(this);

    while(states.size() > GameConfiguration::MAX_STATE_QUEUE_SIZE) {
        states.pop_back();
    }
}

std::shared_ptr<EntityState> Entity::getCurrentState() {
    return states.empty() ? nullptr : states.front();
}

void Entity::setSpeed(const cocos2d::Vec2& speed) {
    this->speed = speed;
}
