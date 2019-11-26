#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include "cocos2d.h"
#include "Map.h"
#include <memory>

using std::shared_ptr;

const float MOVE_TIME = 0.1f;

class Map;

class Player: public cocos2d::Node {
public:
    enum Direction { LEFT, UP, RIGHT, DOWN, NONE};
    CREATE_FUNC(Player);
    static Player* createPlayer();

    bool init();
    void update(float delta);

    void setMap(shared_ptr<Map> gameMap);
    void setDirection(Direction direction);

    void setAlive(bool alive);
    bool isAlive() const { return alive; }
private:
    void captureCells();
    void movePlayer();
    cocos2d::Vec2 getDirectionVector(Direction direction);

    bool alive;

    Direction direction;
    Direction previousDirection;

    float moveTimer;

    shared_ptr<Map> gameMap;
};

#endif // ENTITY_H_INCLUDED
