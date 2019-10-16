#ifndef PAWN_H_INCLUDED
#define PAWN_H_INCLUDED

#include "cocos2d.h"
#include <vector>

#include "StateBar.h"
#include "Skill.h"
#include "conf.h"

void drawConnectPointsWithLines(cocos2d::DrawNode* node,cocos2d::Vec2* points,size_t pointCount,cocos2d::Color4F color=cocos2d::Color4F::WHITE);

class Pawn : public cocos2d::DrawNode {
public:
    static Pawn* createPawn(cocos2d::Vec2* points,size_t pointsNumber);
    virtual bool init();

    void setSpeed(const cocos2d::Vec2& speed);
    cocos2d::Vec2 getSpeed() const { return speed; }

    void setMaximalSpeed(double speed) {
        maximalSpeedLength = speed;
    }

    double getMaximalSpeedLength() const {
        return maximalSpeedLength;
    }

    void setColor(cocos2d::Color4F color);
    cocos2d::Color4F getColor() { return color; }

    void setHealth(double value);
    void setMaximalHealth(double value);

    double getHealth() const { return health; }
    double getMaximalHealth() const;

    virtual void setContentSize(const cocos2d::Size& size);

    virtual void removeFromParentAndCleanup(bool cleanup);
    virtual void setParent(cocos2d::Node* parent);
    virtual void update(float delta);

    virtual void onCollision(Pawn* pawn);

    void setPoints(cocos2d::Vec2* points,size_t pointsNumber);

    void setVisibleHealthBar(bool visible) { healthBar->setVisible(visible); }
    bool isVisibleHealthBar() const { return healthBar->isVisible(); }

    void setTorsionSpeed(double speed) {
        torsionSpeed = speed;
    }

protected:
    std::vector<cocos2d::Vec2> points;
    virtual void drawFigure(bool autoClear=true);
private:

    cocos2d::Color4F color;
    cocos2d::Vec2 speed;

    double maximalSpeedLength;
    double torsionSpeed;

    double health;
    double maxHealth;
    StateBar* healthBar;

};

class Fireball: public Pawn {
public:
    static Fireball* createFireball(float radius);

protected:
    void drawFigure(bool autoClear = true);

private:
    float radius;
};

#include <deque>

class SkillManager;

class Player : public Pawn {
public:
    static Player* createPlayer(cocos2d::Vec2* points,size_t pointsNumber);
    ~Player();

    bool init();
    void setDistorionCount(size_t count);
    size_t getDistortionCount() const { return distortionCount; }
    void update(float delta);

    void setTailLength(int length) { tailLength = length; }
    int getTailLength() const { return tailLength; }

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
protected:
    virtual void drawFigure(bool autoClear=true);
private:
    cocos2d::DrawNode* tail;
    int tailLength;
    size_t distortionCount;
    std::deque<std::pair<cocos2d::Vec2,double>> states;

    SkillManager* skillManager;

};


#endif // PAWN_H_INCLUDED
