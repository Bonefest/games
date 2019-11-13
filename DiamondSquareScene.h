#ifndef DIAMONDSQUARESCENE_H_INCLUDED
#define DIAMONDSQUARESCENE_H_INCLUDED

#include "cocos2d.h"
#include "TestScene.h"
#include "../cocoslib/DiamondSquare.h"

class DiamondSquareScene: public TestScene {
public:
    CREATE_FUNC(DiamondSquareScene);
    static DiamondSquareScene* createScene();
    bool init();


    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event);
private:
    DiamondSquare generator;
    cocos2d::DrawNode* mapDrawer;
    cocos2d::Color4F getColor(double height);

    void drawMap();
};

#endif // DIAMONDSQUARESCENE_H_INCLUDED
