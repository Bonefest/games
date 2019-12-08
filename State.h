#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include "cocos2d.h"
#include "Entity.h"

class Entity;

class EntityState {
public:
    virtual ~EntityState() { }
    virtual void onEnter(Entity* entity) { }
    virtual void onKeyPressed(Entity* entity, cocos2d::EventKeyboard::KeyCode key) { }
    virtual void handleInput(Entity* entity, cocos2d::EventKeyboard::KeyCode key) { }
    virtual void update(Entity* entity, float delta) { }
    virtual void onKeyReleased(Entity* entity, cocos2d::EventKeyboard::KeyCode key) { }
    virtual void onExit(Entity* entity) { }
};


class StandingState: public EntityState {
public:
    void onKeyPressed(Entity* entity, cocos2d::EventKeyboard::KeyCode key);
    void onEnter(Entity* entity) { cocos2d::log("Standing"); }
//TODO таймер "простаивания" и проигрывания анимации простоя
};

enum MOVING_DIR {DIR_LEFT, DIR_UP, DIR_RIGHT, DIR_DOWN , DIR_NONE};

MOVING_DIR getMovingDir(cocos2d::EventKeyboard::KeyCode key);

//Проблема: если мы хотим двигаться по диагонали.
//Решение: добавить обработку в состояние нажатия клавиши и дополнительно прибавлять ещё
//скорость по другой оси.
class MovingState: public EntityState {
public:
    MovingState(MOVING_DIR direction);

    void onEnter(Entity* entity);
    void onKeyPressed(Entity* entity, cocos2d::EventKeyboard::KeyCode key);
    void onKeyReleased(Entity* entity, cocos2d::EventKeyboard::KeyCode key);
private:
    cocos2d::Vec2 calculateDirectionVector(MOVING_DIR direction);

    MOVING_DIR direction;
    std::list<cocos2d::EventKeyboard::KeyCode> pressedKeys;
};

#endif // STATE_H_INCLUDED
