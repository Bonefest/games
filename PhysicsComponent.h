#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

#include "cocos2d.h"

namespace {
    cocos2d::Vec2 DEFAULT_GRAVITY = cocos2d::Vec2(0.0f, -250.0f);
}

class PhysicsComponent: public cocos2d::Component {
public:
    CREATE_FUNC(PhysicsComponent)
    static PhysicsComponent* createComponent();

    virtual bool init();
    virtual void update(float delta);

    void setGravity(const cocos2d::Vec2& gravity);
    void setVelocity(const cocos2d::Vec2& velocity);
    void setGravityEnabled(bool enabled);

    inline bool isGravityEnabled() const { return gravityEnabled; }
    inline cocos2d::Vec2 getGravity() const { return gravity; }
    inline cocos2d::Vec2 getVelocity() const { return velocity; }



private:
    bool gravityEnabled;
    cocos2d::Vec2 gravity;

    cocos2d::Vec2 velocity;
    cocos2d::Vec2 acceleration;
};

#endif // PHYSICSCOMPONENT_H_