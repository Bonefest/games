#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
    static Player* createPlayer();
    bool init();
    CREATE_FUNC(Player);

    void onCollision(cocos2d::Sprite* sprite);

    void force();

    void update(float delta);

    bool isAlive() const { return alive; }

    float getVerticalSpeed() const { return verticalSpeed; }
    void setVerticalSpeed(float speed) { verticalSpeed = speed; }
    cocos2d::Rect getBoundingBox() const;
private:

    float torqueSpeed;
    float verticalSpeed;

    bool alive;
};

#endif // PLAYER_H_INCLUDED
