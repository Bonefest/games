#include "ObjectManager.h"

void MeteorManager::addObject(Pawn* pawn) {
    objects.push_back(pawn);
}

void MeteorManager::removeObject(Pawn* pawn) {
    objects.remove(pawn);
}

void MeteorManager::update(float delta) {
    cocos2d::Vec2 playerPosition = gameScene->getChildByName("Player")->getPosition();
    cocos2d::Vec2 pawnPosition = cocos2d::Vec2::ZERO;
    cocos2d::Vec2 pawnSpeed = cocos2d::Vec2::ZERO;
    for(Pawn* pawn: objects) {
        pawn->update(delta);
        pawnPosition = pawn->getPosition();
        pawnSpeed = pawn->getSpeed();

        cocos2d::Vec2 dirVector(playerPosition);
        dirVector.subtract(pawnPosition);

        double distance = dirVector.length();
        dirVector.normalize();

        pawnSpeed.add(dirVector*delta*1000/distance);
        pawn->setSpeed(pawnSpeed);

        if(isOutOfVisible(pawn)) {
            reverseObjectSpeed(pawn);
        }
    }
}

bool MeteorManager::isOutOfVisible(const Pawn* object) {
    if(object) {
        cocos2d::Vec2 position = object->getPosition();
        cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
        return (position.x > visibleSize.width || position.y > visibleSize.height ||
                position.x < 0 || position.y < 0);
    }
    return true;
}

void MeteorManager::reverseObjectSpeed(Pawn* object) {
    if(object) {
        object->setSpeed(-object->getSpeed());
    }
}


/////////////////////////////////////////////////////////////////////////////


void CollisionManager::addObject(Pawn* pawn) {
    objects.push_back(pawn);
}

void CollisionManager::removeObject(Pawn* pawn) {
    objects.remove(pawn);
}

void CollisionManager::update(float delta) {
    for(auto objIterA = objects.begin();objIterA != objects.end();objIterA++) {
        auto objIterB = objIterA;
        for(objIterB++;objIterB != objects.end();objIterB++) {
            if(isObjectsCollide(*objIterA,*objIterB)) {
                onCollisionMeteors(*objIterA,*objIterB);
                (*objIterA)->onCollision(*objIterB);
                (*objIterB)->onCollision(*objIterA);
                //Коллизия во-первых неидеальна: нужно реализовать коллизию в своих методах.
                //Сейчас это невозможно т.к при изменении скорости в 1, во 2 она изменится обратно.
                //Нужно так же добавить проверку коллизии в фаербол.
            }
        }
    }
}

void CollisionManager::onCollisionMeteors(Pawn* objectA,Pawn* objectB) {
    cocos2d::Vec2 tempSpeed = objectA->getSpeed();
    objectA->setSpeed(objectB->getSpeed());
    objectB->setSpeed(tempSpeed);
}


bool CollisionManager::isObjectsCollide(const Pawn* A,const Pawn* B) {
    return A->getBoundingBox().intersectsRect(B->getBoundingBox());
}
