#ifndef OBJECTMANAGER_H_INCLUDED
#define OBJECTMANAGER_H_INCLUDED

#include "cocos2d.h"
#include "Pawn.h"
#include <list>

/*

Необходимо:

Добавить возможность использования двух навыков: ускорения и призрачности
Обработка столкновений с кораблем (static_cast<Player*>(getChildByName("Player")) и т.д)
Раздвоение/Растроение метеоритов
Стрельба
Меню

ХпБар, который можно прикрепить к объекту и который будет позицинироваться с ним

*/

/*

ObjectManager - абстрактный класс, который определяет интерфейс для управляющего
класса

*/
class ObjectManager {
public:
    virtual void addObject(Pawn* pawn)=0;
    virtual void removeObject(Pawn* pawn)=0;
    virtual void update(float delta)=0;

};

/*

MeteorManager - класс, который управляет добавленными в него метеорами

*/
class MeteorManager : public ObjectManager {
public:
    virtual void addObject(Pawn* pawn);
    virtual void removeObject(Pawn* pawn);
    void setScene(cocos2d::Scene* scene) { gameScene = scene; }
    void update(float delta);


    //void testCollideWithBullet(Pawn* pawn)
    void testCollideWithPlayer(Pawn* pawn);

private:
    void onCollisionWithMeteor(Pawn* objectA,Pawn* objectB);
    void reverseObjectSpeed(Pawn* object);
    bool isOutOfVisible(const Pawn* object);
    bool isObjectsCollide(const Pawn* objectA,const Pawn* objectB);

    std::list<Pawn*> objects;
    cocos2d::Scene* gameScene;
};


class CollisionManager: public ObjectManager {
public:
    virtual void addObject(Pawn* pawn);
    virtual void removeObject(Pawn* pawn);
    void update(float delta);

private:
    bool isObjectsCollide(const Pawn* objectA,const Pawn* objectB);
    void onCollisionMeteors(Pawn* objectA,Pawn* objectB);

    std::list<Pawn*> objects;
};

#endif // OBJECTMANAGER_H_INCLUDED
