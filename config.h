#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "cocos2d.h"

const float GROUND_SPEED = 100.0f;
const float GRAVITY_ACCELERATION = 200.0f;
const float TORQUE_ACCELERATION = 360.0f;

const float MAX_TUBE_HEIGHT = 0.75f*cocos2d::Director::getInstance()->getVisibleSize().height;
const float MIN_TUBE_HEIGHT = 100.0f;
const float MAX_TUBE_SPACE = 96.0f;
const float MIN_TUBE_SPACE = 64.0f;
const float TUBE_SPEED = 100.0f;

const int BASE_GROUND_TAG = 0x1;
const int PLAYER_TAG = 0x2;
const int TUBE_TAG = 0x3;

#endif // CONFIG_H_INCLUDED
