#include "State.h"


MOVING_DIR getMovingDir(cocos2d::EventKeyboard::KeyCode key) {
     if(key == GameConfiguration::MOVE_LEFT) return DIR_LEFT;
     else if(key == GameConfiguration::MOVE_RIGHT) return DIR_RIGHT;
     else if(key == GameConfiguration::MOVE_UP) return DIR_UP;
     else if(key == GameConfiguration::MOVE_DOWN) return DIR_DOWN;

    return DIR_NONE;
}

void StandingState::onKeyPressed(Entity* entity, cocos2d::EventKeyboard::KeyCode key) {
    MOVING_DIR movingDirection = getMovingDir(key);
    if(movingDirection != DIR_NONE) {
        std::shared_ptr<MovingState> newState = std::make_shared<MovingState>(movingDirection);
        newState->onKeyPressed(entity, key);
        entity->addNewState(newState);
    }
}

MovingState::MovingState(MOVING_DIR dir):direction(dir) { }

void MovingState::onEnter(Entity* entity) {
    cocos2d::log("Moving state");
    switch(direction) {
    case DIR_LEFT:  entity->runAnimation(LEFT);  break;
    case DIR_RIGHT: entity->runAnimation(RIGHT); break;
    case DIR_UP:    entity->runAnimation(UP);    break;
    case DIR_DOWN:  entity->runAnimation(DOWN);  break;
    }
}

void MovingState::onKeyPressed(Entity* entity, cocos2d::EventKeyboard::KeyCode key) {

    if(getMovingDir(key) != DIR_NONE) {
        pressedKeys.push_back(key);
        cocos2d::Vec2 speed = entity->getSpeed() + calculateDirectionVector(getMovingDir(key))*100;
        entity->setSpeed(speed);

        //TEMP - над выделить onEnter код в отдельную функцию
        direction = getMovingDir(key);
        onEnter(entity);
    }
}

void MovingState::onKeyReleased(Entity* entity, cocos2d::EventKeyboard::KeyCode key) {
    if(getMovingDir(key) != DIR_NONE) {
        pressedKeys.remove(key);
        cocos2d::Vec2 speed = entity->getSpeed() - calculateDirectionVector(getMovingDir(key))*100;
        entity->setSpeed(speed);

        if(pressedKeys.empty()) {
            entity->stopActionByTag(CURRENT_ANIMATION_TAG);
            entity->addNewState(std::make_shared<StandingState>());
        }
    }
}

cocos2d::Vec2 MovingState::calculateDirectionVector(MOVING_DIR direction) {
    switch(direction) {
    case DIR_LEFT: return cocos2d::Vec2(-1, 0);
    case DIR_UP: return cocos2d::Vec2(0, 1);
    case DIR_RIGHT: return cocos2d::Vec2(1, 0);
    case DIR_DOWN: return cocos2d::Vec2(0, -1);
    }

    return cocos2d::Vec2::ZERO;
}
