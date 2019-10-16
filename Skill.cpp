#include "Skill.h"
#include "conf.h"

Skill::Skill(double duration,double cooldown) {
    setDuration(duration);
    setCooldown(cooldown);

    activated = false;
}

void Skill::setDuration(double value) {
    duration = value;
}

void Skill::setCooldown(double value) {
    cooldown = value;
}


bool Skill::isRefreshing() const {
    return !isActivated() && getElapsedTimeSinceStopping() < getCooldown();
}

double Skill::getElapsedTimeSinceActivation() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastActivatingTimePoint).count();
}

double Skill::getElapsedTimeSinceStopping() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastStoppingTimePoint).count();
}

void Skill::use() {
    if(!isActivated()) {
        activated = true;
        refreshed = false;
        lastActivatingTimePoint = std::chrono::system_clock::now();
        onUse();
    }
}


void Skill::stop() {
    if(isActivated()) {
        activated = false;
        lastStoppingTimePoint = std::chrono::system_clock::now();
        onStop();
    }
}

bool Skill::isReadyToUse() const {
    //return !isActivated() && (lastStoppingTimePoint == 0 || getElapsedTimeSinceStopping() > cooldown);
    return !isActivated() && (getElapsedTimeSinceStopping() > cooldown);
}

///////////////////////////////////////////////////////////////////////////////////

Boost::Boost(Player* owner):Skill(BOOST_DURATION,BOOST_COOLDOWN) {
    this->owner = owner;
}

void Boost::onUse() {
    owner->setTailLength(200);
    owner->setMaximalSpeed(owner->getMaximalSpeedLength() + 40);
    owner->setSpeed(owner->getSpeed()*1.5);
}

void Boost::onStop() {
    owner->setTailLength(0);
    owner->setMaximalSpeed(owner->getMaximalSpeedLength() - 40);
    owner->setSpeed(owner->getSpeed()/1.5);
}

Ghost::Ghost(Player* owner):Skill(GHOST_DURATION,GHOST_COOLDOWN) {
    this->owner = owner;
}


void Ghost::onUse() {
    owner->setTailLength(500);
    cocos2d::Color4F color = owner->getColor();
    color.a = 0.3f;
    owner->setColor(color);
}

void Ghost::onStop() {
    owner->setTailLength(0);
}

void Ghost::onRefreshed() {
    cocos2d::Color4F color = owner->getColor();
    color.a = 1.0f;
    owner->setColor(color);
}

SkillFireball::SkillFireball(Player* owner):Skill(FIREBALL_DURATION,FIREBALL_COOLDOWN) {
    this->owner = owner;
}

void SkillFireball::onUse() {

    Fireball* createdFireball = Fireball::createFireball(FIREBALL_SIZE);
    createdFireball->scheduleUpdate();
    createdFireball->setVisibleHealthBar(false);

    cocos2d::Vec2 ownerDirection(std::cos(toRad(owner->getRotation())), std::sin(-toRad(owner->getRotation())));
    createdFireball->setSpeed(owner->getSpeed() + ownerDirection*FIREBALL_SPEED);

    auto fireballSequence = cocos2d::Sequence::create(cocos2d::DelayTime::create(FIREBALL_LIFETIME),
                                                      cocos2d::FadeOut::create(0.5f),
                                                      cocos2d::CallFuncN::create([](cocos2d::Node* node){

        node->removeFromParentAndCleanup(true);
    }),nullptr);
    createdFireball->runAction(fireballSequence);

    auto fireballPosition = owner->getPosition() + ownerDirection*32;
    createdFireball->setPosition(owner->getPosition() + ownerDirection*32);

    owner->getParent()->addChild(createdFireball);
}

void SkillFireball::onStop() {

}

///////////////////////////////////////////////////////////////////////////////////


SkillManager::~SkillManager() {
    for(auto skillIter = skillTable.begin();skillIter != skillTable.end();skillIter++) {
        delete skillIter->second;
    }
}

void SkillManager::addSkill(Skill* skill,const std::string& name) {
    if(!hasSkill(name)) {
        skillTable[name] = skill;
    }
}

void SkillManager::removeSkill(const std::string& name) {
    skillTable.erase(name);
}

bool SkillManager::isSkillActivated(const std::string& name) {
    if(hasSkill(name)) {
        return skillTable[name]->isActivated();
    }
    return false;
}

bool SkillManager::isSkillRefreshing(const std::string& name) {
    if(hasSkill(name)) {
        return skillTable[name]->isRefreshing();
    }
    return false;
}

void SkillManager::activateSkill(const std::string& name) {
    if(hasSkill(name)) {
        if(skillTable[name]->isReadyToUse())
            skillTable[name]->use();
    }
}

void SkillManager::stopSkill(const std::string& name) {
    if(hasSkill(name)) {
        skillTable[name]->stop();
    }
}

void SkillManager::update(float delta) {
    for(auto skillIter = skillTable.begin();skillIter != skillTable.end();skillIter++) {
        if( skillIter->second->getElapsedTimeSinceActivation() > skillIter->second->getDuration()
             && skillIter->second->isActivated()) {
                skillIter->second->stop();
        } else if(!skillIter->second->isActivated() && skillIter->second->getElapsedTimeSinceStopping() > skillIter->second->getCooldown()
            && !skillIter->second->isRefreshed()) {
                skillIter->second->refresh();
            }
    }
}

bool SkillManager::hasSkill(const std::string& name) const {
    return skillTable.find(name) != skillTable.end();
}
