#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include "cocos2d.h"
#include "Entity.h"

using std::vector;

class Player;

const int MAP_SIZE = 48;

class Map {
public:
	enum CellType {CAPTURED,ACTIVATED,EMPTY,DIED};
	struct Cell {
		CellType type;
		Player* owner;
	};

	Map(uint32_t mapSize);

	void setCell(int32_t x, int32_t y, Cell cell);
	Cell getCell(int32_t x, int32_t y);

    int32_t getMapSize() const { return mapData.size(); }

private:

	vector<vector<Cell>> mapData;
	uint32_t mapSize;
};

#endif // MAP_H_INCLUDED
