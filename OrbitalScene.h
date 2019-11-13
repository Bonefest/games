#ifndef ORBITALSCENE_H_INCLUDED
#define ORBITALSCENE_H_INCLUDED

#include "TestScene.h"
#include "PhysicsComponent.h"
#include "../cocoslib/KeyManager.h"

/*
Необходим либо класс Circle,Square и т.д.Либо класс Drawer,
в который будут добавляться объекты с видом фигуры, которой
её необходимо отрисовывать. Класс Drawer просто будет пробегать
по всем объектам и в зависимости от типа объекта - рисовать его
по-разному.
*/

/*

В каждый момент времени к планете, которая притягивется -
добавляется скорость, которая имеет то же значение, но
меняется с ориентацией тела.

*/

class OrbitalScene: public TestScene {
public:
    CREATE_FUNC(OrbitalScene);
    static OrbitalScene* createScene();

    bool init();
    void initPlanets();
    void initEventListeners();

    void onMouseDown(cocos2d::EventMouse* event);
    void onMouseMove(cocos2d::EventMouse* event);
    void onMouseUp(cocos2d::EventMouse* event);

    void update(float delta);
private:
    void drawNodes();
    void calculatePhysics(float delta);

    KeyManager keyManager;

    cocos2d::DrawNode* drawer;

    cocos2d::Node* planetOne, *planetTwo;
    PhysicsComponent *componentOne, *componentTwo;

    cocos2d::Size visibleSize;
};


#endif // ORBITALSCENE_H_INCLUDED
