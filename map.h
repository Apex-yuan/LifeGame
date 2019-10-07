#ifndef __MAP_H
#define __MAP_H

#include "point.h"

#define MAP_WIDTH   400
#define MAP_HEIGHT  300

class Map
{
    public:
    Map();
    ~Map();
    void setValue(Point point, bool status);
    void setValue(int x, int y, bool status);
    bool getValue(Point point);
    bool getValue(int x, int y);
    int getWidth(void);
    int getHeight(void);
    private:
    bool value[MAP_WIDTH][MAP_HEIGHT];
    const int width;
    const int height;
};



#endif /* __MAP_H */

