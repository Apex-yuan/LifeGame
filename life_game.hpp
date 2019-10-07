#ifndef __LIFE_GAME_H
#define __LIFE_GAME_H

#include "point.h"
#include "map.h"

#define WIDTH  400
#define HEIGHT 300



class LifeGame
{
    public:
    LifeGame();
    ~LifeGame();

    // static void setMapStatus(Point point, bool status);
    // static void setMapStatus(int x, int y, bool status);
    // static bool getMapStatus(Point point);
    // static bool getMapStatus(int x, int y);
    void iteration(Map &map);
    private:
    // static bool map[WIDTH][HEIGHT];
    int getNumAround(Map &map, Point point);
    bool survivalRule(Map &map, Point point);
};

#endif /* __LIFE_GAME */

