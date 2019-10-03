#ifndef __LIFE_GAME_H
#define __LIFE_GAME_H

#define WIDTH  400
#define HEIGHT 300

typedef struct
{
    int x;
    int y;
}Point;

extern bool map[WIDTH][HEIGHT];

int getNumAround(Point point);
void upedateMap(void);

#endif /* __LIFE_GAME */

