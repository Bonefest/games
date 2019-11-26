#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include <memory>
#include <vector>

#include "cocos2d.h"
#include "Map.h"
#include "Entity.h"

using std::shared_ptr;
using std::vector;


class View : public cocos2d::DrawNode {
public:
    CREATE_FUNC(View);
    static View* createView();

    bool init();

	void setMap(shared_ptr<Map> map);
	void setBlockSize(float size);
	void setMiddleDisplacement(cocos2d::Vec2 displacement);

	void drawView();

    void setPlayers(const std::vector<Player*> players);
private:
    void initUI();

    void drawCell(Map::Cell cell, int32_t x, int32_t y);
    cocos2d::Color4F getCellColor(Map::Cell cell);

	shared_ptr<Map> gameMap;

	float blockSize;
	cocos2d::Vec2 middleDisplacement;
	cocos2d::Size visibleSize;

	std::vector<Player*> players;

	cocos2d::Label* scoreLeftBottom;
	cocos2d::Label* scoreLeftTop;
	cocos2d::Label* scoreRightTop;
	cocos2d::Label* scoreRightBottom;
};


#endif // VIEW_H_INCLUDED
