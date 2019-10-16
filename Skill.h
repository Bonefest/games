#ifndef SKILL_H_INCLUDED
#define SKILL_H_INCLUDED

#include <chrono>
#include <map>
#include <string>

#include "Pawn.h"

class Pawn;
class Player;

class Skill {
public:
    Skill(double duration,double cooldown);

    void use();
    void stop();
    void refresh() { refreshed = true; onRefreshed(); }

    bool isReadyToUse() const;
    bool isActivated() const { return activated; }
    bool isRefreshing() const;
    bool isRefreshed() const { return refreshed; }

    double getElapsedTimeSinceActivation() const;
    double getElapsedTimeSinceStopping() const;


    void setDuration(double duration);
    void setCooldown(double cooldown);

    double getDuration() const { return duration; }
    double getCooldown() const { return cooldown; }

protected:
    virtual void onUse()=0;
    virtual void onStop()=0;
    virtual void onRefreshed() {}

private:
    double duration;
    double cooldown;

    bool activated;
    bool refreshed;

    std::chrono::system_clock::time_point lastActivatingTimePoint;
    std::chrono::system_clock::time_point lastStoppingTimePoint;
};

class Boost : public Skill {
public:
    Boost(Player* owner);

protected:
    void onUse();
    void onStop();

private:
    Player* owner;
};


class Ghost: public Skill {
public:
    Ghost(Player* owner);

protected:
    void onUse();
    void onStop();
    void onRefreshed();

private:
    Player* owner;
};

class SkillFireball: public Skill {
public:
    SkillFireball(Player* owner);

protected:
    void onUse();
    void onStop();

private:
    Player* owner;
};

///////////////////////////////////////////////////////////////////////////////////


class SkillManager {
public:
    ~SkillManager();

    void addSkill(Skill* skill,const std::string& name);
    void removeSkill(const std::string& name);

    bool isSkillActivated(const std::string& name);
    bool isSkillRefreshing(const std::string& name);
    void activateSkill(const std::string& name);
    void stopSkill(const std::string& name);

    bool hasSkill(const std::string& name) const;

    void update(float delta);

private:
    Player* owner;
    std::map<std::string,Skill*> skillTable;
};

#endif // SKILL_H_INCLUDED
