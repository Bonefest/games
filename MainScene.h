#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED

#include "cocos2d.h"
#include "../cocoslib/KeyManager.h"
#include <stack>

USING_NS_CC;

struct PPoint {
    int x;
    int y;
};

const int MAP_SIZE = 32;

class MainScene: public Scene {
public:
    CREATE_FUNC(MainScene);
    static MainScene* createScene();
    bool init();
    void initListeners();
    void initDrawer();
    void findCellSize();

    void update(float delta);

    void onKeyPressed(EventKeyboard::KeyCode key, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode key, Event* event);

private:
    void generateMap();
    void depthFirst();
    void autoFill();
    bool isAvailable(int x, int y);

    std::stack<std::pair<PPoint, PPoint>> points;
    bool visited[MAP_SIZE][MAP_SIZE];
    int gameMap[MAP_SIZE*2][MAP_SIZE*2];

    KeyManager keyManager;
    DrawNode* drawer;

    Size visibleSize;
    Size cellSize;
};

#endif // MAINSCENE_H_INCLUDED
