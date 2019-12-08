#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED

#include "cocos2d.h"
#include "InputHandler.h"

USING_NS_CC;

class GameScene: public Scene {
public:
    CREATE_FUNC(GameScene);
    static GameScene* createScene();
    bool init();
    bool initListeners();

    void onKeyPressed(EventKeyboard::KeyCode key, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode key, Event* event);

    void update(float delta);
private:
    InputHandler inputHandler;
};

#endif // GAMESCENE_H_INCLUDED
