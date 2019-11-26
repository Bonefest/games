#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED

#include <vector>

#include "cocos2d.h"
#include "View.h"
#include "Entity.h"
#include "InputHandler.h"
#include "../cocoslib/KeyManager.h"

const int MAX_PLAYERS = 4;

class MainScene: public cocos2d::Scene {
public:
    CREATE_FUNC(MainScene);
    static MainScene* createScene();
    bool init();

    void update(float delta);

private:
    void initListeners();
    void initMap();
    void initPlayers();
    void initCommands();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event);

    //CONTROLLER
    void removePlayer(Player* player);

    View* view;

    std::vector<Player*> players;
    shared_ptr<Map> gameMap;

    cocos2d::Size visibleSize;

    KeyManager keyManager;
    InputHandler inputHandler;
};

#endif // MAINSCENE_H_INCLUDED
