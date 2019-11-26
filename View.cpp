#include "View.h"

View* View::createView() {
    return View::create();
}

bool View::init() {
    if(!cocos2d::DrawNode::init()) return false;

    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    initUI();

    return true;
}

void View::initUI() {
    scoreLeftBottom = cocos2d::Label::createWithTTF("","fonts/arial.ttf", 26.0f);
    scoreLeftBottom->setColor(cocos2d::Color3B::BLACK);
    scoreLeftBottom->setPosition(cocos2d::Vec2::ZERO);
    scoreLeftBottom->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(scoreLeftBottom);

    scoreLeftTop = cocos2d::Label::createWithTTF("","fonts/arial.ttf", 26.0f);
    scoreLeftTop->setColor(cocos2d::Color3B::BLACK);
    scoreLeftTop->setPosition(0, visibleSize.height);
    scoreLeftTop->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
    addChild(scoreLeftTop);

    scoreRightTop = cocos2d::Label::createWithTTF("","fonts/arial.ttf", 26.0f);
    scoreRightTop->setColor(cocos2d::Color3B::BLACK);
    scoreRightTop->setPosition(visibleSize.width, visibleSize.height);
    scoreRightTop->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_RIGHT);
    addChild(scoreRightTop);

    scoreRightBottom = cocos2d::Label::createWithTTF("","fonts/arial.ttf", 26.0f);
    scoreRightBottom->setColor(cocos2d::Color3B::BLACK);
    scoreRightBottom->setPosition(visibleSize.width, 0);
    scoreRightBottom->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_RIGHT);
    addChild(scoreRightBottom);

}

void View::setMap(shared_ptr<Map> map) {
    this->gameMap = map;
}

void View::setPlayers(std::vector<Player*> players) {
    this->players = players;
}

void View::drawView() {
    clear();

    int colorCounter[players.size()]{};

    int32_t mapSize = gameMap->getMapSize();
    for(int32_t y = 0;y < mapSize;y++) {
        for(int32_t x = 0;x < mapSize;x++) {
            Map::Cell cell = gameMap->getCell(x, y);
            for(int i = 0;i < players.size();++i) {
                if(players[i] == cell.owner) {
                    colorCounter[i]++;
                    break;
                }
            }

            drawCell(cell, x, y);
        }
    }

    const char* format = "[Score: %d]";
    scoreLeftBottom->setString("hello!");

    scoreLeftBottom->setString(cocos2d::StringUtils::format(format, colorCounter[0]));
    scoreLeftTop->setString(cocos2d::StringUtils::format(format, colorCounter[1]));
    scoreRightTop->setString(cocos2d::StringUtils::format(format, colorCounter[2]));
    scoreRightBottom->setString(cocos2d::StringUtils::format(format, colorCounter[3]));

}

void View::drawCell(Map::Cell cell, int32_t x, int32_t y) {
    cocos2d::Vec2 from = blockSize*cocos2d::Vec2(x,y) + middleDisplacement;
    cocos2d::Vec2 to = blockSize*cocos2d::Vec2::ONE + middleDisplacement + blockSize*cocos2d::Vec2(x,y);
    cocos2d::Color4F color = getCellColor(cell);

    for(Player* player: players) {
        if(!player->isAlive()) continue;

        if(int32_t(player->getPositionX()) == x && int32_t(player->getPositionY() == y)) {
            color = cocos2d::Color4F(player->getColor());
            color = cocos2d::Color4F(color.r * 0.5, color.g * 0.5, color.b * 0.5, color.a);
            break;
        }
    }

    switch(cell.type) {
    case Map::CellType::EMPTY: {
        drawRect(from, to, color);
        //drawCircle((from + to) / 2,blockSize/2,1.0,12,false, color);
    }
    break;

    case Map::CellType::DIED:
    case Map::CellType::CAPTURED:
    case Map::CellType::ACTIVATED: {
        drawSolidRect(from, to, color);
        //drawSolidCircle((from + to) / 2,blockSize/2,1.0,12, color);
    }

    break;

    }
}

cocos2d::Color4F View::getCellColor(Map::Cell cell) {
    switch(cell.type) {

    case Map::CellType::CAPTURED:
    case Map::CellType::ACTIVATED: return (cell.owner == nullptr)?cocos2d::Color4F::BLACK : cocos2d::Color4F(cell.owner->getColor());

    case Map::CellType::EMPTY: return cocos2d::Color4F::BLACK;
    case Map::CellType::DIED: return cocos2d::Color4F::GRAY;

    }

    return cocos2d::Color4F::BLACK;
}

void View::setBlockSize(float size) {
    blockSize = size;
}

void View::setMiddleDisplacement(cocos2d::Vec2 displacement) {
    middleDisplacement = displacement;
}
