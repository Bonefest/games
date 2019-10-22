#include "TubeManager.h"
#include "config.h"

void TubeManager::generateTubePair() {
    float bottomTubeY = cocos2d::RandomHelper::random_real(MIN_TUBE_HEIGHT,MAX_TUBE_HEIGHT);
    float upperTubeY = bottomTubeY + cocos2d::RandomHelper::random_real(MIN_TUBE_SPACE,MAX_TUBE_SPACE);

    cocos2d::Sprite* bottomTube = cocos2d::Sprite::createWithSpriteFrameName("pipe-green.png");
    bottomTube->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width + bottomTube->getContentSize().width, bottomTubeY));

    cocos2d::Sprite* upperTube = cocos2d::Sprite::createWithSpriteFrameName("pipe-green.png");
    upperTube->setPosition(cocos2d::Vec2(cocos2d::Director::getInstance()->getVisibleSize().width + bottomTube->getContentSize().width, upperTubeY + upperTube->getContentSize().height));
    upperTube->setFlippedY(true);

    scene->addChild(bottomTube, -3, TUBE_TAG);
    scene->addChild(upperTube, -3, TUBE_TAG);
    tubes.push_back(std::make_pair(bottomTube, upperTube));
}

void TubeManager::update(float delta) {
    for(auto tubeIter = tubes.begin(); tubeIter != tubes.end() ;) {
        tubeIter->first->setPositionX(tubeIter->first->getPositionX() - TUBE_SPEED*delta);
        tubeIter->second->setPositionX(tubeIter->second->getPositionX() - TUBE_SPEED*delta);

        if(tubeIter->first->getPositionX() < -tubeIter->first->getContentSize().width/2) {
                tubeIter->first->removeFromParentAndCleanup(true);
                tubeIter->second->removeFromParentAndCleanup(true);
                tubeIter = tubes.erase(tubeIter);
        }
        else tubeIter++;
    }
}

bool TubeManager::areTubesCollideWithSprite(cocos2d::Sprite* sprite) {
    for(auto tubeIter = tubes.begin();tubeIter != tubes.end();tubeIter++) {
        if(sprite->getBoundingBox().intersectsRect(tubeIter->first->getBoundingBox()) ||
           sprite->getBoundingBox().intersectsRect(tubeIter->second->getBoundingBox())) return true;
    }
    return false;
}
