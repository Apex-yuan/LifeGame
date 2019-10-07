#ifndef __DRAW_H
#define __DRAW_H

#include <GL/glut.h>
#include "point.h"
#include "map.h"

#define MAP_WIDTH     400
#define MAP_HEIGHT    300
#define WINDOW_WIDTH  (80 * MESH_SIZE)
#define WINDOW_HEIGHT (60 * MESH_SIZE) 
#define POINT_SIZE    10.0f  //像素
#define MESH_SIZE     10


#define GLUT_WHEEL_UP    3
#define GLUT_WHEEL_DOWN  4

#define FPS   5



class Draw
{
    public:
    Draw( Map *map_);
    ~Draw();
    static void init(int argc, char *argv[]);
    static void display(void);
    static void onMouse(int button,int state,int x,int y);
    static void onMotion(int x, int y);
    static void keyboard(unsigned char key, int x, int y);

    static bool map_update_flag;     //用于触发地图更新事件
    static bool map_current_status;  //用于记录当前地图处于更新状态还是暂停状态
    private:
    static Map *map;
    static Point window_center;      //记录窗口中心点相对于map的坐标位置
    static Point middle_down_window_center; //记录中建按下时窗口的中心位置
    
    static int mesh_size;
    static int point_size;
    static Point middle_up;           //用于记录中建弹起的坐标位置
    static Point middle_down;  //用于记录中建按下的坐标位置
    static bool left_down_flag;
    static bool right_down_flag;
    static bool middle_down_flag;
    static float zoom;

    static void drawMap(void);
    static void drawMesh(float mesh_size_);
    

};


#endif /* __DRAW_H */
