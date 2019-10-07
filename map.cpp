#include "map.h"

Map::Map() : width(MAP_WIDTH), height(MAP_HEIGHT){
    for(int i = 0; i <  MAP_WIDTH; ++i) {
        for(int j = 0; j < MAP_HEIGHT; ++j) {
            value[i][j] = 0;
        }
    }
}

Map::~Map() {

}

void Map::setValue(Point point, bool status) {
    value[point.x][point.y] = status;
}

void Map::setValue(int x, int y, bool status) {
    value[x][y] = status;
}

bool Map::getValue(Point point) {
    return value[point.x][point.y];
}

bool Map::getValue(int x, int y) {
    return value[x][y];
}

int Map::getWidth(void)
{
    return width;
}

int Map::getHeight(void)
{
    return height;
}