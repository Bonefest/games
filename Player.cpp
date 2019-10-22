#include "Player.h"
#include "config.h"

Player* Player::createPlayer() {
    return Player::create();
}

bool Player::init() {
    if(!cocos2d::Sprite::init()) {
        return false;
    }

    verticalSpeed = 0.0f;
    torqueSpeed = 0.0f;
    alive = true;

    return true;
}

void Player::update(float delta) {
    if(getPositionY() <= 0.1*cocos2d::Director::getInstance()->getVisibleSize().height) return;

    verticalSpeed -= GRAVITY_ACCELERATION * delta;
    torqueSpeed   -= TORQUE_ACCELERATION * delta;

    if(torqueSpeed < -TORQUE_ACCELERATION) torqueSpeed = -TORQUE_ACCELERATION;
    else if(torqueSpeed > 450.0f) torqueSpeed = 450.0f;

    setPositionY(getPositionY() + verticalSpeed*delta);

    float rotation = getRotation() - torqueSpeed*delta;
    if(rotation > 90.0f) rotation = 90.0f;
    else if(rotation < -45.0f) { rotation = -45.0f; torqueSpeed -= 360.0*delta; }

    setRotation(rotation);
}

void Player::force() {
    if(isAlive()) {
        verticalSpeed = std::max(0.0f,verticalSpeed);
        verticalSpeed += 0.50f*GRAVITY_ACCELERATION;

        torqueSpeed = std::max(0.0f, torqueSpeed);
        torqueSpeed += 450.0f;
    }
}

cocos2d::Rect Player::getBoundingBox() const {
    cocos2d::Rect bbox = cocos2d::Sprite::getBoundingBox();
    bbox.setRect(bbox.getMinX()+10,bbox.getMinY()+10,bbox.size.width-10,bbox.size.height-10);
    return bbox;
}

void Player::onCollision(cocos2d::Sprite* sprite) {
    alive = false;
}
