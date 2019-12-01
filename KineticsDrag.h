#ifndef KINETICSDRAG_H_INCLUDED
#define KINETICSDRAG_H_INCLUDED

#include "cocos2d.h"
#include "TestScene.h"
#include "PhysicsComponent.h"

class KineticsDragScene : public TestScene {
public:
    CREATE_FUNC(KineticsDragScene);
    static KineticsDragScene* createScene();
    bool init();

    void update(float delta);

    void onMouseDown(cocos2d::EventMouse*);
    void onMouseUp(cocos2d::EventMouse*);
    void onMouseMove(cocos2d::EventMouse*);

private:
    void initObjects();
    bool windBoxClicked;

    cocos2d::Size visibleSize;

    cocos2d::Sprite* projectile;
    PhysicsComponent* projectileComponent;

    cocos2d::Node* windBox;
    cocos2d::Vec2 windEndPoint;

    cocos2d::Vec2 clickedPosition;
    cocos2d::Vec2 mousePosition;
};


#endif // KINETICSDRAG_H_INCLUDED
