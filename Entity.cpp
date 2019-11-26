#include "Entity.h"

Player* Player::createPlayer() {
    return Player::create();
}

bool Player::init() {
    if(!cocos2d::Node::init()) return false;

    alive = true;
    previousDirection = direction = NONE;
    moveTimer = 0.0f;

    return true;
}

void Player::setMap(shared_ptr<Map> map) {
    gameMap = map;
}

void Player::setDirection(Direction dir) {
    if( (dir + 2) % 4 != previousDirection) {
        direction = dir;
    }
}

void Player::update(float delta) {
    moveTimer += delta;
    if(moveTimer >= MOVE_TIME) {
        while(moveTimer >= MOVE_TIME) {
            movePlayer();
            moveTimer -= MOVE_TIME;
        }
        moveTimer = 0.0f;
    }
}

void Player::movePlayer() {
    cocos2d::Vec2 playerPosition = getPosition();
    playerPosition.add(getDirectionVector(direction));

    if(playerPosition.x >= 0 && playerPosition.y >= 0 &&
       playerPosition.x < gameMap->getMapSize() && playerPosition.y < gameMap->getMapSize()) {
        Map::Cell cell = gameMap->getCell(int(playerPosition.x), int(playerPosition.y));
        if(cell.owner == this) captureCells();
        else if(cell.owner != nullptr && cell.type == Map::CellType::ACTIVATED) {
            cell.owner->setAlive(false);
        }

        gameMap->setCell(int(playerPosition.x),int(playerPosition.y),
                     Map::Cell{Map::CellType::ACTIVATED, this});
    }

    previousDirection = direction;
    setPosition(playerPosition);

}


void Player::captureCells() {
    int32_t mapSize = gameMap->getMapSize();
    for(int32_t y = 0; y < mapSize; ++y) {
        for(int32_t x = 0; x < mapSize; ++x) {
            int r = x, l = x, u = y, d = y;
            while(r < mapSize) { if(gameMap->getCell(r, y).owner == this) break; r++; }
            while(l >= 0) { if(gameMap->getCell(l, y).owner == this) break; l--; }
            while(u >= 0) { if(gameMap->getCell(x, u).owner == this) break; u--; }
            while(d < mapSize) { if(gameMap->getCell(x, d).owner == this) break; d++; }

            if(r < mapSize && d < mapSize && l >= 0 && u >= 0) {
                gameMap->setCell(x, y, {Map::CellType::CAPTURED, this});
            }
        }
    }
}



cocos2d::Vec2 Player::getDirectionVector(Direction dir) {
    switch(dir) {
    case LEFT: return cocos2d::Vec2(-1, 0);
    case UP: return cocos2d::Vec2(0, 1);
    case RIGHT : return cocos2d::Vec2(1, 0);
    case DOWN: return cocos2d::Vec2(0, -1);
    }

    return cocos2d::Vec2::ZERO;
}

void Player::setAlive(bool alive) {
    this->alive = alive;
}
