#ifndef SLINGSHOTSCENE_H_
#define SLINGSHOTSCENE_H_

#include "cocos2d.h"
#include "../cocoslib/KeyManager.h"

#include "TestScene.h"
#include "PhysicsComponent.h"

USING_NS_CC;

const float TRAJECTORY_STEP = 0.05f;

class SlingshotScene : public TestScene {
public:
    CREATE_FUNC(SlingshotScene);
    static SlingshotScene* createScene();
    bool init();

    void update(float delta);

    void onMouseMove(cocos2d::EventMouse* event);
    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseUp(cocos2d::EventMouse* event);

    void drawTrajectory(const cocos2d::Vec2& initialVelocity, const cocos2d::Vec2& initialPosition, float timeStep, const cocos2d::Color4F& color = cocos2d::Color4F::RED);
protected:

private:
    KeyManager keyManager;

    cocos2d::Size visibleSize;

    bool clicked;
    cocos2d::Vec2 cursorPosition;
    cocos2d::Vec2 lastClickPosition;

    PhysicsComponent* component;
};

#endif // SLINGSHOTSCENE_H_
