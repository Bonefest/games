#ifndef PARTICLESCENE_H_INCLUDED
#define PARTICLESCENE_H_INCLUDED

#include "TestScene.h"
#include "../cocoslib/KeyManager.h"

//need a slider!
const uint32_t PARTICLE_AMOUNT = 20;
const double MAXIMAL_RADIUS = 40.0;

class ParticleScene : public TestScene {
public:
    CREATE_FUNC(ParticleScene);
    static ParticleScene* createScene();

    bool init();

    void update(float delta);

    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseUp(cocos2d::EventMouse* event);
    //void onMouseMove(cocos2d::EventMouse* event);

private:
    std::vector<cocos2d::Sprite*> particles;
    float getCircleRadius();

    KeyManager keyManager;
    cocos2d::Vec2 pressed;
};


#endif // PARTICLESCENE_H_INCLUDED
