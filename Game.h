#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

class Game {
public:
    static Game* getInstance();
    void initGameWithScene(Scene* scene);

    void setCurrentScene(Scene* scene);
    Scene* getCurrentScene();

    void setPlayer(Entity* entity);
    Entity* getPlayer();
    //Level* getCurrentLevel();

    //void setGameState(GameState* state);
    //GameState* getCurrentGameState();
private:
    Game() { }
    Game(const Game&);

    Entity* player;
    Scene* currentScene;

};

#endif // GAME_H_INCLUDED
