#ifndef CONF_H_INCLUDED
#define CONF_H_INCLUDED

#include <vector>
#include "cocos2d.h"

#define toRad(angle) ((M_PI/180.0) * angle)

const float ACCELERATION = 60.0f;
const float SPEED_LIMIT = 250.0f;
const float ROTATING = 4.0f;

const int START_METEOR_COUNT = 5;

const float BOOST_DURATION = 1000.0f;
const float BOOST_COOLDOWN = 2000.0f;

const float GHOST_DURATION = 1500.0f;
const float GHOST_COOLDOWN = 2000.0f;

const float FIREBALL_DURATION = 1.0f;
const float FIREBALL_LIFETIME = 2.0f;
const float FIREBALL_COOLDOWN = 3000.0f;
const float FIREBALL_SPEED = 10.0f;
const int   FIREBALL_SIZE = 10.0f;

const int METEOR_TAG = 1;

std::vector<cocos2d::Vec2> getMeteorPoints();
std::vector<cocos2d::Vec2> getFireballPoints();
#endif // CONF_H_INCLUDED
