#ifndef __DRAW_H
#define __DRAW_H

#include <GL/glut.h>
#include "point.h"

#define MESH_SIZE     10
#define WINDOW_WIDTH  (80 * MESH_SIZE)
#define WINDOW_HEIGHT (60 * MESH_SIZE) 
#define POINT_SIZE    10.0f  //像素


#define GLUT_WHEEL_UP    3
#define GLUT_WHEEL_DOWN  4

#define FPS   5



class Draw
{
    public:
    Draw();
    ~Draw();
    void drawMap(void);
    void drawMesh(float mesh_size_);
    void display(void);
    void onMouse(int button,int state,int x,int y);
    void onMotion(int x, int y);
    void keyboard(unsigned char key, int x, int y);

    private:
    // LifeGame lifegame;
    Point window_center;      //记录窗口中心点相对于map的坐标位置
    Point middle_down_window_center; //记录中建按下时窗口的中心位置
    bool map_update_flag;     //用于触发地图更新事件
    bool map_current_status;  //用于记录当前地图处于更新状态还是暂停状态
    int mesh_size;
    int point_size;
    Point middle_up;           //用于记录中建弹起的坐标位置
    Point middle_down;  //用于记录中建按下的坐标位置
    bool left_down_flag;
    bool right_down_flag;
    bool middle_down_flag;
    float zoom;
    

};


#endif /* __DRAW_H */
