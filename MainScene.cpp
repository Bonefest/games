#include "MainScene.h"
#include <vector>
#include <algorithm>

MainScene* MainScene::createScene() {
    return MainScene::create();
}

bool MainScene::init() {
    if(!Scene::init()) {
        log("[Error] Unable to initialize MainScene!");
        return false;
    }
    srand(time(0));

    visibleSize = Director::getInstance()->getVisibleSize();

    initListeners();
    initDrawer();
    findCellSize();

    generateMap();

    scheduleUpdate();
    return true;
}


void MainScene::initListeners() {
    EventListenerKeyboard* klistener = EventListenerKeyboard::create();
    klistener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    klistener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(klistener, this);
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode key, Event* event) {
    keyManager.setKey(key);
    if(key == EventKeyboard::KeyCode::KEY_R)
        generateMap();
    else if(key == EventKeyboard::KeyCode::KEY_A)
        autoFill();
}

void MainScene::autoFill() {
    while(!points.empty())
        depthFirst();
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode key, Event* event) {
    keyManager.removeKey(key);
}

void MainScene::initDrawer() {
    drawer = DrawNode::create();
    this->addChild(drawer);
}

void MainScene::findCellSize() {
    float cellSide = std::min(visibleSize.width, visibleSize.height) / (2.0f * MAP_SIZE);
    cellSize = Size(cellSide, cellSide);
}

void MainScene::generateMap() {
    for(int i = 0;i<MAP_SIZE*MAP_SIZE;++i)
        visited[i/MAP_SIZE][i%MAP_SIZE] = false;

    for(int y = 0;y < MAP_SIZE*2;++y) {
        for(int x = 0;x < MAP_SIZE*2;++x) {
            gameMap[y][x] = ( (y + 1) % 2 ) ? ( (x + 1) % 2 ) ? 1 : 0 : 0;
        }
    }
    PPoint startPoint = {random(0, MAP_SIZE - 1), random(0, MAP_SIZE - 1)};
    points.push(std::make_pair(startPoint, startPoint));
}


void MainScene::depthFirst() {
    if(points.empty()) return;

    int x,y;

    std::pair<PPoint, PPoint> point = points.top();
    x = point.first.x; y = point.first.y;

    points.pop();
    if(visited[y][x]) return;

    visited[y][x] = true;
    gameMap[point.second.y][point.second.x] = 1;


    std::vector<PPoint> adjacent;
    if(isAvailable(x - 1, y)) adjacent.push_back({x - 1, y});
    if(isAvailable(x + 1, y)) adjacent.push_back({x + 1, y});
    if(isAvailable(x, y + 1)) adjacent.push_back({x, y + 1});
    if(isAvailable(x, y - 1)) adjacent.push_back({x, y - 1});

    std::random_shuffle(adjacent.begin(), adjacent.end());

    for(PPoint& adj : adjacent) {
        if(!visited[adj.y][adj.x]) {
            points.push(std::make_pair(adj, PPoint{int((2*y + 2*adj.y) / 2),
                                                   int((2*x + 2*adj.x) / 2)}));

        }
    }

}

bool MainScene::isAvailable(int x,int y) {
    return (x >= 0 && x < MAP_SIZE && y >= 0 && y < MAP_SIZE);
}

void MainScene::update(float delta) {
    drawer->clear();
    for(int y = 0;y < 2*MAP_SIZE;++y) {
        for(int x = 0;x < 2*MAP_SIZE;++x) {
            if(gameMap[y][x]) {
                Vec2 source(x*cellSize.width, y*cellSize.height);
                drawer->drawSolidRect(source, source + Vec2(cellSize), Color4F::WHITE);
            }
        }
    }

    if(keyManager.isKeyPressed(EventKeyboard::KeyCode::KEY_W)) depthFirst();
}
