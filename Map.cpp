#include "Map.h"

Map::Map(uint32_t size) {
    mapSize = size;

    for(uint32_t y = 0;y < mapSize;y++) {
        mapData.push_back(vector<Cell>());
        for(uint32_t x = 0;x < mapSize;x++) {
            mapData[y].push_back(Cell{EMPTY, nullptr});
        }
    }

}

void Map::setCell(int32_t x, int32_t y, Cell cell) {
    if(x >= 0 && y >= 0 && x < mapSize && y < mapSize) {
        mapData[y][x] = cell;
    }
}

Map::Cell Map::getCell(int32_t x, int32_t y) {
    return mapData[y][x];
}
