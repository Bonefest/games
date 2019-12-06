#include "Entity.h"
#include "GameConfiguration.h"

Entity* Entity::createEntity() {
    return Entity::create();
}

bool Entity::init() {
    if(!Sprite::init()) return false;

    speed = cocos2d::Vec2::ZERO;

    return true;
}

void Entity::runAnimation(AnimationType type) {
    auto animationIter = animations.find(type);
    if(animationIter != animations.end()) {
        runAction(cocos2d::Animate::create(animationIter->second));
    }
    //else animationDefault
}

void Entity::setAnimation(AnimationType type, cocos2d::Animation* animation) {
    animations[type] = animation;
}

void Entity::addNewState(EntityState* state) {
    states.push_front(state);

    while(states.size() > GameConfiguration::MAX_STATE_QUEUE_SIZE) {
        delete states.back();
        states.pop_back();
    }
}

EntityState* Entity::getCurrentState() {
    return states.empty() ? nullptr : states.front();
}

void Entity::setSpeed(const cocos2d::Vec2& speed) {
    this->speed = speed;
}
