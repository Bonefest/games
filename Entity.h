#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "cocos2d.h"
#include "GameConfiguration.h"
#include "State.h"
#include <deque>
#include <map>
#include <string>

enum AnimationType {
    IDLE, UP, LEFT, RIGHT, DOWN
};

class Entity: public cocos2d::Sprite {
public:

    void runAnimation(AnimationType type);
    void setAnimation(AnimationType type, cocos2d::Animation*);

    void addNewState(EntityState* state);
    EntityState* getCurrentState();
private:
    std::map<AnimationType, cocos2d::Animation*> animations;
    std::deque<EntityState*> states;
};

//AbstractFactory
//createHuman
//createOrc
//createEtc

#endif // ENTITY_H_INCLUDED
