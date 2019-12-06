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

class EntityState;

class Entity: public cocos2d::Sprite {
public:
    CREATE_FUNC(Entity);
    static Entity* createEntity();
    bool init();

    void runAnimation(AnimationType type);
    void setAnimation(AnimationType type, cocos2d::Animation*);

    void addNewState(EntityState* state);
    EntityState* getCurrentState();

    void setSpeed(const cocos2d::Vec2& speed);
    inline cocos2d::Vec2 getSpeed() { return speed; }
private:
    std::map<AnimationType, cocos2d::Animation*> animations;
    std::deque<EntityState*> states;

    cocos2d::Vec2 speed;
};

//AbstractFactory
//createHuman
//createOrc
//createEtc

#endif // ENTITY_H_INCLUDED
