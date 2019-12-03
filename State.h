#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "Entity.h"

class Entity;

class EntityState {
public:
    virtual ~EntityState();
    virtual void onEnter(Entity* entity) { }
    virtual void onKeyPressed(Entity* entity, cocos2d::EventKeyboard::Key key) { }
    virtual void handleInput(Entity* entity, cocos2d::EventKeyboard::Key key) { }
    virtual void onKeyReleased(Entity* entity, cocos2d::EventKeyboard::Key key) { }
    virtual void onExit(Entity* entity) { }
};


class StandingState: public EntityState {
public:
    void onKeyPressed(Entity* entity, cocos2d::EventKeyboard::Key key) {
        if(key == GameConfiguration::MOVE_LEFT) {
            //entity->addNewState(new MovingState(LEFT));
        }
    }
};

#endif // STATE_H_INCLUDED
