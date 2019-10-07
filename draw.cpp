#include <GL/glut.h>
#include "life_game.hpp"
#include <iostream>
#include "draw.h"
#include "point.h"

/*
 * g++ draw_window.cpp -o draw_window -lGL -lGLU -lglut
 * 编译时一定要加上-lGL -lGLU -lglut 否则会出现no reference的错误
 */


Map *Draw::map = NULL;
// LifeGame *Draw::lifegame = NULL;
int Draw::mesh_size = MESH_SIZE;
int Draw::point_size = POINT_SIZE;
float Draw::zoom = 1.0;
bool Draw::left_down_flag = 0;
bool Draw::right_down_flag = 0;
bool Draw::middle_down_flag = 0;
Point Draw::window_center = {0,0};
//Point Draw::window_center.y = HEIGHT / 2;
Point Draw::middle_down_window_center = window_center;
bool Draw::map_update_flag = 0;
bool Draw::map_current_status = 0;
Point Draw::middle_up = {0, 0};           //用于记录中建弹起的坐标位置
Point Draw::middle_down = {0, 0};  //用于记录中建按下的坐标位置

Draw::Draw( Map *map_)
{
    map = map_;
    // lifegame = lifegame_;
    mesh_size = MESH_SIZE;
    point_size = POINT_SIZE;
    zoom = 1.0;
    left_down_flag = 0;
    right_down_flag = 0;
    middle_down_flag = 0;
    window_center.x = WIDTH / 2;
    window_center.y = HEIGHT / 2;
    middle_down_window_center = window_center;
    map_update_flag = 0;
    map_current_status = 0;

}
Draw::~Draw()
{
    
}

void Draw::init(int argc, char *argv[])
{
    glutInit(&argc, argv);
    /*窗口使用单焕存，并且使用RGB颜色模型 */
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    /*设置窗口左上角的位置 */
    glutInitWindowPosition(500, 200);
    /*设置窗口的宽高 */
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    /*创建窗口，传入参数为窗口标题 */
    glutCreateWindow("Life Game");

    /*初始化OpenGL配置 */
    /*设置窗口的背景色 */
    glClearColor(0.0, 0.0, 0.0, 0.8);
    /*设置投影类型：正投影 */
    glMatrixMode(GL_PROJECTION);
    /*观察参数：x坐标值从0-800，y坐标值从0-600 */
    // glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
    /*设定点的尺寸，单位：像素 */
    // glPointSize(PIXEL_SIZE);
}

void Draw::drawMesh(float mesh_size_)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.10, 0.10, 0.10);
    glLineWidth(1);
    glBegin(GL_LINES);
    //横向
    for(float i = 0; i <= WINDOW_HEIGHT/2; i += mesh_size_)
    {
        glVertex2f(-WINDOW_WIDTH/2, i);
        glVertex2f(WINDOW_WIDTH/2, i);
    }
    for(float i = 0; i >= -WINDOW_HEIGHT/2; i -= mesh_size_)
    {
        glVertex2f(-WINDOW_WIDTH/2, i);
        glVertex2f(WINDOW_WIDTH/2, i);
    }
    //纵向
    for(float i = 0; i <= WINDOW_WIDTH/2; i += mesh_size_)
    {
        glVertex2f(i, -WINDOW_HEIGHT/2);
        glVertex2f(i, WINDOW_HEIGHT/2);
    }
    for(float i = 0; i >= -WINDOW_WIDTH/2; i -= mesh_size_)
    {
        glVertex2f(i, -WINDOW_HEIGHT/2);
        glVertex2f(i, WINDOW_HEIGHT/2);
    }
    glEnd();
    glColor3f(0.15, 0.15, 0.15);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(-400, 0);
    glVertex2i(400, 0);
    glVertex2i(0, -300);
    glVertex2i(0, 300);

    glEnd();
}

void Draw::drawMap(void)
{
    point_size = POINT_SIZE * zoom;
    glPointSize(point_size);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    //第一象限
    for(float i = point_size/2 ; i < WINDOW_WIDTH/2; i += point_size)
    {
        for(float j = point_size/2  ; j < WINDOW_HEIGHT/2; j+=point_size)
        {
            //将点从窗口像素坐标系映射到map坐标系
            Point tmp;
            tmp.x = int(window_center.x + i /point_size);
            tmp.y = int(window_center.y + j /point_size);
            
            if((*map).getValue(tmp) == true)
            {
                glVertex2f(i,j);
            }
        }
    }
    //第二象限
    for(float i = -point_size/2 ; i > -WINDOW_WIDTH/2; i -= point_size)
    {
        for(float j = point_size/2  ; j < WINDOW_HEIGHT/2; j+=point_size)
        {
            //将点从窗口像素坐标系映射到map坐标系
            Point tmp;
            tmp.x = int(window_center.x + i /point_size);
            tmp.y = int(window_center.y + j /point_size);
            
            if((*map).getValue(tmp) == true)
            {
                glVertex2f(i,j);
            }
        }
    }
    //第三象限
    for(float i = -point_size/2 ; i > -WINDOW_WIDTH/2; i -= point_size)
    {
        for(float j = -point_size/2  ; j > -WINDOW_HEIGHT/2; j-=point_size)
        {
            //将点从窗口像素坐标系映射到map坐标系
            Point tmp;
            tmp.x = int(window_center.x + i /point_size);
            tmp.y = int(window_center.y + j /point_size);
            
            if((*map).getValue(tmp) == true)
            {
                glVertex2f(i,j);
            }
        }
    }
    //第四象限
    for(float i = point_size/2 ; i < WINDOW_WIDTH/2; i += point_size)
    {
        for(float j = -point_size/2  ; j > -WINDOW_HEIGHT/2; j-=point_size)
        {
            //将点从窗口像素坐标系映射到map坐标系
            Point tmp;
            tmp.x = int(window_center.x + i /point_size);
            tmp.y = int(window_center.y + j /point_size);
            
            if((*map).getValue(tmp) == true)
            {
                glVertex2f(i,j);
            }
        }
    }
    glEnd();
    glFlush();
}

void Draw::display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   
    drawMesh(mesh_size);
    drawMap();
    glFlush();
}

void Draw::onMouse(int button,int state,int x,int y)
{
    //将鼠标坐标装换为左下角为
    float i = x / 1.0/ point_size;
    float j = (WINDOW_HEIGHT - y)/1.0 / point_size;
    //讲鼠标坐标映射到map坐标系
    int m = i - WINDOW_WIDTH / 2.0 / point_size + window_center.x ;
    int n = j - WINDOW_HEIGHT / 2.0 / point_size + window_center.y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // LifeGame::setMapStatus(m,n,true);
        (*map).setValue(m, n, true);
        left_down_flag = 1;
        std::cout << " SIZE:(" << point_size << " " << mesh_size << ")" << std::endl;
        std::cout << "MOUSE LEFT DOWN:(" << i << " " << j << ")" << std::endl;
        std::cout << "MAP(m,n):(" << m << " " << n << ")" << std::endl;
    }
    else
    {
        left_down_flag = 0;
    }

    /*右键事件处理 */
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        (*map).setValue(m, n, false);
        right_down_flag = 1;
        // std::cout << i << " " << j << std::endl;
    }
    else
    {
        right_down_flag = 0;
    }

    /*滚轮按下事件处理 */
    if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
    {
        std::cout << "WHEEL DOWN" << i << " " << j <<  std::endl;
        middle_down_flag = 1;
        middle_down.x = i;
        middle_down.y = j;
        middle_down_window_center = window_center;
    }
    else
    {
        middle_down_flag = 0;      
    }  
    
    if(button == GLUT_WHEEL_UP && state == GLUT_UP)
    {
        (zoom <= 5)? zoom+=0.1 : zoom = 5.1;
        point_size = POINT_SIZE * zoom;
        mesh_size = MESH_SIZE * zoom;
        // std::cout << zoom << std::endl;
    }
    if(button == GLUT_WHEEL_DOWN && state == GLUT_DOWN)
    {
        if((window_center.x - WINDOW_WIDTH/point_size/2 <= 0) ||
           (window_center.y - WINDOW_HEIGHT/point_size/2 <= 0) || 
           (window_center.x + WINDOW_WIDTH/point_size/2 >= WIDTH) ||
           (window_center.y + WINDOW_HEIGHT/point_size/2 >= HEIGHT) )

        {
            zoom =zoom;
        }
        else
        {
            (zoom >= 0.5)? zoom-=0.1 : zoom = 0.4;
        }
        point_size = POINT_SIZE * zoom;
        mesh_size = MESH_SIZE * zoom;
        // std::cout << zoom << std::endl;
    }   
}

void Draw::onMotion(int x, int y)
{
    float i = x /1.0/ point_size;
    float j = (WINDOW_HEIGHT - y) /1.0/ point_size;
    int m = i - WINDOW_WIDTH/2.0/point_size+window_center.x;
    int n = j - WINDOW_HEIGHT/2.0/point_size+window_center.y;

    if(left_down_flag == 1)
    {
        (*map).setValue(m, n, true);
        // std::cout << "MOUSE LEFT DOWN:(" << x << " " << y << ")" << std::endl;
    }
    if(right_down_flag == 1)
    {
        (*map).setValue(m, n, false);
    }
    if(middle_down_flag == 1)
    {
        std::cout << "WHEEL UP:" << i << " " << j << std::endl;
        middle_up.x = i;
        middle_up.y = j;
        window_center.x = middle_down_window_center.x - (middle_up.x - middle_down.x);
        window_center.y = middle_down_window_center.y - (middle_up.y - middle_down.y);
        std::cout << "CENTER XY:" << window_center.x << " " << window_center.y << std::endl;

        //限幅处理
        if(window_center.x + WINDOW_WIDTH/point_size/2 >= WIDTH)
        {
            window_center.x = WIDTH - WINDOW_WIDTH/point_size/2;
        }
        if(window_center.x - WINDOW_WIDTH/point_size/2 <= 0)
        {
            window_center.x = WINDOW_WIDTH/point_size/2;
        }
        if(window_center.y + WINDOW_HEIGHT/point_size/2 >= HEIGHT)
        {
            window_center.y = HEIGHT - WINDOW_HEIGHT/point_size/2;
        }
        if(window_center.y - WINDOW_HEIGHT/point_size/2 <= 0)
        {
            window_center.y = WINDOW_HEIGHT/point_size/2;
        }

    }
    
}

void Draw::keyboard(unsigned char key, int x, int y)
{
    if(key == ' ' )
    {
        
        if(map_current_status == 1)
        {
            map_update_flag = 0;
            std::cout << "KEY:" << key << " "  << map_update_flag <<  std::endl;
        }
        if(map_current_status == 0)
        {
            map_update_flag = 1;
            std::cout << "KEY:" << key << " "  << map_update_flag <<  std::endl;
        }
    }
    
}
