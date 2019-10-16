#include "Factory.h"


#include <vector>

/*

Объект-магнит, который при появлении изменяет вектора скоростей всех объектов
направленную на себя

*/

Pawn* MeteorFactory::createNewMeteor() {
    auto points = getMeteorPoints();

    float randomSize = cocos2d::random(1.0f,2.0f);
    for(size_t i = 0;i<points.size();++i) {
        points[i].add(cocos2d::Vec2(cocos2d::random(-3.0f,3.0f),cocos2d::random(-3.0f,3.0f)));
        points[i] = (randomSize*points[i]);
    }


    //Определение самой крайней нижней точки и самой крайней верхней точки
    float minx(points[0].x),maxx(points[0].x),miny(points[0].y),maxy(points[0].y);
    for(int i = 0;i<points.size();++i) {
        minx = std::min(minx,points[i].x);
        miny = std::min(miny,points[i].y);

        maxx = std::max(maxx,points[i].x);
        maxy = std::max(maxy,points[i].y);
    }

    Pawn* meteor = Pawn::createPawn(points.data(),points.size());
    meteor->setContentSize(cocos2d::Size(4*(maxx-minx)/5.0,4*(maxy-miny)/5.0));
    meteor->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
    meteor->setSpeed(cocos2d::Vec2(cocos2d::random(-20.0,20.0),cocos2d::random(-20.0,20.0)));
    meteor->setRotation(cocos2d::random(0.0,360.0));
    meteor->setTorsionSpeed(cocos2d::random(0.0,50.0));


    return meteor;
}
