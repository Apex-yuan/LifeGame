#include "life_game.hpp"
#include "draw.h"
#include "map.h"

Map map;
LifeGame lifegame;
Draw draw(&map);

void onTimer(int value)
{
    if(draw.map_update_flag == 1)
    {
        lifegame.iteration(map);
        draw.map_current_status = 1;
    }
    else
    {
        draw.map_current_status = 0;
    }
    draw.display();
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, onTimer, 1);
}

int main(int argc, char *argv[])
{
    
    draw.init(argc, argv);
    glutMouseFunc(&draw.onMouse);
    glutMotionFunc(&draw.onMotion);
    glutKeyboardFunc(&draw.keyboard);
    glutTimerFunc(1000/FPS, &onTimer,1);
    glutMainLoop();
    return 0;
}