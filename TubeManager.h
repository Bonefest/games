#ifndef TUBEMANAGER_H_INCLUDED
#define TUBEMANAGER_H_INCLUDED

#include "cocos2d.h"
#include <list>


class TubeManager {
public:

    void setScene(cocos2d::Scene* scene) { this->scene = scene; }
    void generateTubePair();
    void update(float delta);

    bool areTubesCollideWithSprite(cocos2d::Sprite* sprite);
private:
    cocos2d::Scene* scene;
    std::list<std::pair<cocos2d::Sprite*,cocos2d::Sprite*>> tubes;
};


#endif // TUBEMANAGER_H_INCLUDED
