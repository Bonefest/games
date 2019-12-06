#include "State.h"

void StandingState::onKeyPressed(Entity* entity, cocos2d::EventKeyboard::KeyCode key) {
     if(key == GameConfiguration::MOVE_LEFT) entity->addNewState(new MovingState(DIR_LEFT));
     else if(key == GameConfiguration::MOVE_RIGHT) entity->addNewState(new MovingState(DIR_RIGHT));
     else if(key == GameConfiguration::MOVE_UP) entity->addNewState(new MovingState(DIR_UP));
     else if(key == GameConfiguration::MOVE_DOWN) entity->addNewState(new MovingState(DIR_DOWN));
}

MovingState::MovingState(MOVING_DIR dir):direction(dir) { }

void MovingState::onEnter(Entity* entity) {
    switch(direction) {
    case DIR_LEFT: { entity->setSpeed(cocos2d::Vec2(-100.0, 0.0)); entity->runAnimation(LEFT); } break;
    case DIR_RIGHT: { entity->setSpeed(cocos2d::Vec2(100.0, 0.0)); entity->runAnimation(RIGHT); } break;
    case DIR_UP: { entity->setSpeed(cocos2d::Vec2(0.0, 100.0)); entity->runAnimation(UP); } break;
    case DIR_DOWN: { entity->setSpeed(cocos2d::Vec2(0.0,-100.0)); entity->runAnimation(DOWN); } break;
    }
}
