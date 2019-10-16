#include "Pawn.h"

Pawn* Pawn::createPawn(cocos2d::Vec2* objPoints,size_t pointsNumber) {
    Pawn* pawn = new Pawn();
    if(pawn->init()) {
        pawn->autorelease();
        pawn->setPoints(objPoints,pointsNumber);
        return pawn;
    }
    CC_SAFE_DELETE(pawn);
    return nullptr;
}


bool Pawn::init() {
    color = cocos2d::Color4F::WHITE;
    speed = cocos2d::Vec2::ZERO;
    torsionSpeed = 0.0;
    health = maxHealth = 100.0f;

    healthBar = StateBar::createStateBar(cocos2d::Size::ZERO,cocos2d::Color4F(1.0f,0,0,0.5f));
    healthBar->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
    healthBar->setValue(health);
    healthBar->setMaxValue(maxHealth);

    return DrawNode::init();
}
void Pawn::setPoints(cocos2d::Vec2* objPoints,size_t pointsNumber) {
    points.clear();
    double maxX = 0.0,maxY = 0.0;
    for(size_t i = 0;i<pointsNumber;++i) {
        points.push_back(objPoints[i]);
        if(objPoints[i].x > maxX) maxX = objPoints[i].x;
        if(objPoints[i].y > maxY) maxY = objPoints[i].y;
    }
    setContentSize(cocos2d::Size(maxX,maxY));
}


void Pawn::onCollision(Pawn* pawn) {

}

void Pawn::update(float delta) {
    drawFigure();
    setHealth(getHealth()-delta*5);

    cocos2d::Vec2 pawnPosition = getPosition();
    if(healthBar) {
        cocos2d::Vec2 healthBarPosition = pawnPosition;
        healthBarPosition.subtract(cocos2d::Vec2(0.0,1.5*getContentSize().height));
        healthBar->setPosition(healthBarPosition);
    }

    setRotation(std::fmod((getRotation() + torsionSpeed*delta),360.0f));
    pawnPosition.add(delta*speed);
    setPosition(pawnPosition);
}

void Pawn::drawFigure(bool autoClear) {

    size_t pointsSize = points.size();
    if(pointsSize > 1) {
        if(autoClear) clear();

        drawConnectPointsWithLines(this,points.data(),points.size(),getColor());
    }

    if(healthBar)
        healthBar->drawBar();

    /////////
    auto sze = getContentSize();
    drawLine(cocos2d::Vec2(sze.width/2,sze.height/2),cocos2d::Vec2(sze.width,sze.height/2),cocos2d::Color4F::RED);
    drawLine(cocos2d::Vec2(sze.width/2,sze.height/2),cocos2d::Vec2(sze.width/2,sze.height),cocos2d::Color4F::RED);
}

void Pawn::setSpeed(const cocos2d::Vec2& speed) {
    this->speed = speed;
}

void Pawn::setHealth(double value) {
    health = value;
    healthBar->setValue(value);
}

void Pawn::setMaximalHealth(double value) {
    maxHealth = value;
    healthBar->setMaxValue(value);
}

void Pawn::setColor(cocos2d::Color4F color) {
    this->color = color;
}

void Pawn::setParent(cocos2d::Node* parent) {
    cocos2d::DrawNode::setParent(parent);
    if(parent != nullptr)
        parent->addChild(healthBar);
}

void Pawn::removeFromParentAndCleanup(bool clean) {
    healthBar->removeFromParentAndCleanup(clean);
    cocos2d::DrawNode::removeFromParentAndCleanup(clean);
}

void Pawn::setContentSize(const cocos2d::Size& size) {
    cocos2d::DrawNode::setContentSize(size);
    healthBar->setContentSize(cocos2d::Size(1.5*size.width,10));
}


Fireball* Fireball::createFireball(float radius) {
    Fireball* fireball = new Fireball;
    if(fireball->init()) {
        fireball->autorelease();
        fireball->radius = radius;

        return fireball;
    }

    CC_SAFE_DELETE(fireball);
    return nullptr;
}

void Fireball::drawFigure(bool autoClear) {
    if(autoClear) clear();
    drawCircle(cocos2d::Vec2::ZERO,radius,1.0f,5,false,getColor());
}
//-----------------------------------------------------------------//

#include <iostream>
Player::~Player() {
    std::cout << "DESTRUCTOR\n";
    delete skillManager;
}

bool Player::init() {
    if(Pawn::init()) {
        tail = nullptr;
        tailLength = 0;
        setMaximalSpeed(SPEED_LIMIT);
        skillManager = new SkillManager;
        skillManager->addSkill(new Boost(this),"boost");
        skillManager->addSkill(new Ghost(this),"ghost");
        skillManager->addSkill(new SkillFireball(this),"fireball");

        return true;
    }

    return false;
}

Player* Player::createPlayer(cocos2d::Vec2* points,size_t pointsNumber) {
    Player* player = new Player();
    if(player->init()) {
        player->autorelease();
        player->setPoints(points,pointsNumber);

        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::update(float delta) {
    skillManager->update(delta);

    if(!tail) {
        tail = cocos2d::DrawNode::create();
        getParent()->addChild(tail);
    }

    Pawn::update(delta);
    if(states.size() > tailLength) states.pop_back();
    if(states.size() > tailLength) states.pop_back();

    cocos2d::Vec2 playerPosition = getPosition();
    playerPosition.subtract(cocos2d::Vec2(getContentSize().width/2,getContentSize().height/2));
    states.emplace_front(playerPosition,getRotation());
}

void Player::drawFigure(bool autoClear) {
    if(autoClear) { clear(); tail->clear(); }

    Pawn::drawFigure();

    cocos2d::Color4F newColor = getColor();

    cocos2d::Vec2 playerPos = getPosition();

    for(uint64_t i = ((skillManager->isSkillActivated("ghost") || skillManager->isSkillRefreshing("ghost"))?states.size()-1:0);i<states.size();i++) {
        std::vector<cocos2d::Vec2> oldPoints = points;
        for(auto& rpoint : points) {
            rpoint.rotate(cocos2d::Vec2(getContentSize().width/2,getContentSize().height/2),-3.1415926/180.0*states[i].second);
            rpoint.add(states[i].first);
        }
        if(skillManager->isSkillActivated("ghost") || skillManager->isSkillRefreshing("ghost"))
            newColor.a = 1.0;
        else newColor.a = 0.3-0.3/states.size()*i;

        drawConnectPointsWithLines(tail,points.data(),points.size(),newColor);
        points = oldPoints;
    }
}

void Player::onKeyPressed(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event) {
    if(key == cocos2d::EventKeyboard::KeyCode::KEY_SPACE && !skillManager->isSkillActivated("ghost") && !skillManager->isSkillRefreshing("ghost")) {
        skillManager->activateSkill("boost");
    } else if(key == cocos2d::EventKeyboard::KeyCode::KEY_SHIFT && !skillManager->isSkillActivated("boost")) {
        skillManager->activateSkill("ghost");
    } else if(key == cocos2d::EventKeyboard::KeyCode::KEY_ALT) {
        skillManager->activateSkill("fireball");
    }
}

void Player::onKeyReleased(cocos2d::EventKeyboard::KeyCode key,cocos2d::Event* event) {
    if(key == cocos2d::EventKeyboard::KeyCode::KEY_SPACE) {
        skillManager->stopSkill("boost");
    } else if(key == cocos2d::EventKeyboard::KeyCode::KEY_SHIFT) {
        skillManager->stopSkill("ghost");
    }
}


void drawConnectPointsWithLines(cocos2d::DrawNode* node,cocos2d::Vec2* points,size_t pointCount,cocos2d::Color4F color) {
    if(pointCount > 1) {
        for(size_t i = 0;i<pointCount-1;++i) {
            node->drawLine(points[i],points[i+1],color);
        }
        node->drawLine(points[0],points[pointCount-1],color);
    }
}
