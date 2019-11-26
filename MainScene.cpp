#include "MainScene.h"
#include "Command.h"

MainScene* MainScene::createScene() {
    return MainScene::create();
}


bool MainScene::init() {
    if(!cocos2d::Scene::init())
        return false;

    cocos2d::Director::getInstance()->setClearColor(cocos2d::Color4F::WHITE);

    initListeners();
    initMap();
    initPlayers();
    initCommands();


    scheduleUpdate();
    return true;
}

void MainScene::initListeners() {
    cocos2d::EventListenerKeyboard* keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void MainScene::initMap() {
    gameMap = std::make_shared<Map>(MAP_SIZE);

    float minSize = 0.0f;
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    minSize = std::min(visibleSize.width, visibleSize.height);

    view = View::createView();
    view->setBlockSize(minSize / MAP_SIZE);
    view->setMiddleDisplacement((cocos2d::Vec2(visibleSize) - cocos2d::Vec2::ONE*minSize) * 0.5f);
    view->setMap(gameMap);

    addChild(view);

}

void MainScene::initPlayers() {
    for(int i = 0;i<MAX_PLAYERS;++i) {
        Player* newPlayer = Player::createPlayer();
        newPlayer->setMap(gameMap);
        addChild(newPlayer);
        players.push_back(newPlayer);
    }


    //NEED A CONFIG
    players[0]->setPosition(cocos2d::Vec2::ZERO);
    players[0]->setColor(cocos2d::Color3B::RED);
    players[0]->setDirection(Player::Direction::RIGHT);

    players[1]->setPosition(cocos2d::Vec2(MAP_SIZE-1, 0));
    players[1]->setColor(cocos2d::Color3B::GREEN);
    players[1]->setDirection(Player::Direction::UP);

    players[2]->setPosition(cocos2d::Vec2(MAP_SIZE-1, MAP_SIZE-1));
    players[2]->setColor(cocos2d::Color3B::BLUE);
    players[2]->setDirection(Player::Direction::LEFT);

    players[3]->setPosition(cocos2d::Vec2(0, MAP_SIZE - 1));
    players[3]->setColor(cocos2d::Color3B::YELLOW);
    players[3]->setDirection(Player::Direction::DOWN);

    view->setPlayers(players);
}

void MainScene::initCommands() {
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_A, std::make_shared<Move>(players[0], Player::Direction::LEFT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_W, std::make_shared<Move>(players[0], Player::Direction::UP));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_D, std::make_shared<Move>(players[0], Player::Direction::RIGHT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_S, std::make_shared<Move>(players[0], Player::Direction::DOWN));

    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW, std::make_shared<Move>(players[1], Player::Direction::LEFT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW, std::make_shared<Move>(players[1], Player::Direction::UP));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW, std::make_shared<Move>(players[1], Player::Direction::RIGHT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW, std::make_shared<Move>(players[1], Player::Direction::DOWN));

    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_H, std::make_shared<Move>(players[2], Player::Direction::LEFT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_U, std::make_shared<Move>(players[2], Player::Direction::UP));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_K, std::make_shared<Move>(players[2], Player::Direction::RIGHT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_J, std::make_shared<Move>(players[2], Player::Direction::DOWN));

    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_4, std::make_shared<Move>(players[3], Player::Direction::LEFT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_8, std::make_shared<Move>(players[3], Player::Direction::UP));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_6, std::make_shared<Move>(players[3], Player::Direction::RIGHT));
    inputHandler.setCommandToButton(cocos2d::EventKeyboard::KeyCode::KEY_5, std::make_shared<Move>(players[3], Player::Direction::DOWN));

}

void MainScene::update(float delta) {
    inputHandler.handleInput(keyManager);
    view->drawView();

    for(int i = 0;i<MAX_PLAYERS;++i) {
        if(!players[i]->isAlive()) continue;

        players[i]->update(delta);
        if(int(players[i]->getPositionX()) < 0 || int(players[i]->getPositionY()) < 0 ||
           int(players[i]->getPositionX()) >= MAP_SIZE || int(players[i]->getPositionY()) >= MAP_SIZE) {
            players[i]->setAlive(false);
            removePlayer(players[i]);
        }
    }

    for(int i = 0;i<MAX_PLAYERS;++i) {
        if(!players[i]->isAlive()) removePlayer(players[i]);
    }

}

void MainScene::removePlayer(Player* player) {
    int32_t mapSize = gameMap->getMapSize();
    for(int32_t y = 0;y < mapSize;y++) {
        for(int32_t x = 0;x < mapSize;x++) {
            Map::Cell cell = gameMap->getCell(x, y);
            if(cell.owner == player) {
                cell.owner = nullptr;

                if(cell.type == Map::CellType::ACTIVATED) {
                    cell.type = Map::CellType::EMPTY;
                    gameMap->setCell(x, y, cell);
                } else if(cell.type == Map::CellType::CAPTURED) {
                    cell.type = Map::CellType::DIED;
                    gameMap->setCell(x, y, cell);
                }
            }
        }
    }
}

void MainScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
    keyManager.setKey(key);
}

void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode key, cocos2d::Event* event) {
    keyManager.removeKey(key);
}

/*

class Command {
public:
	virtual void execute(Player* player) = 0;
};

class MoveCommand {
public:
	MoveCommand(cocos2d::Vec2 direction);
	~MoveCommand();
	virtual void execute(Player* player);
private:
	cocos2d::Vec2 direction;
};

class HandleInput {
public:
	Command* handleInput();
	void setGameScene(MainScene* scene);

private:
	KeyManager keyManager;
	MainScene* gameScene;
}

typedef Map<cocos2d::KeyboardEvent::KeyCode, KEY_TYPE> KeyMap

enum KEY_TYPE {LEFT, UP, RIGHT, DOWN, USE}
class Player: public cocos2d::Sprite {
	KeyMap keyMap;
public:

	KeyMap getKeyMap();
}

*/
