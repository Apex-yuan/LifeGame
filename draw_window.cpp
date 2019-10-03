#include <GL/glut.h>
#include "life_game.hpp"
#include <iostream>

/*
 * g++ draw_window.cpp -o draw_window -lGL -lGLU -lglut
 * 编译时一定要加上-lGL -lGLU -lglut 否则会出现no reference的错误
 */

#define WINDOW_WIDTH  800//1855//3296 //800
#define WINDOW_HEIGHT 600//1056//1082 //600
#define POINT_SIZE    10.0f  //像素
#define MESH_SIZE     10

#define GLUT_WHEEL_UP    3
#define GLUT_WHEEL_DOWN  4

#define FPS   5

float point_size = POINT_SIZE;
float mesh_size = MESH_SIZE;
float zoom  = 1;

bool left_down_flag = 0;
bool right_down_flag = 0;
bool middle_down_flag = 0;
int offset_x = 0;
int offset_y = 0;
int window_center_x = WIDTH / 2;
int window_center_y = HEIGHT / 2;
int window_center_old_x = window_center_x;
int window_center_old_y = window_center_y;
bool update_map_flag = 0;
bool current_map_state = 0;

void draw_mesh(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.10, 0.10, 0.10);
    glBegin(GL_LINES);
    //横向
    for(int i = -WINDOW_HEIGHT/2 + mesh_size/2; i <= WINDOW_HEIGHT/2; i += mesh_size)
    {
        glVertex2f(-WINDOW_WIDTH/2, i);
        glVertex2f(WINDOW_WIDTH/2, i);
    }
    //纵向
    for(int i = -WINDOW_WIDTH/2 + mesh_size/2; i <= WINDOW_WIDTH/2; i += mesh_size)
    {
        glVertex2f(i, -WINDOW_HEIGHT/2);
        glVertex2f(i, WINDOW_HEIGHT/2);
    }
    glEnd();
}

void draw_map(void)
{
    point_size = POINT_SIZE * zoom;
    glPointSize(point_size);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);
    // glVertex2i(0,0);
    // std::cout<< "Point Size:" << point_size << std::endl;
    for(int i = -WINDOW_WIDTH/2; i < WINDOW_WIDTH/2; i += point_size)
    {
        for(int j = -WINDOW_HEIGHT/2; j < WINDOW_HEIGHT/2; j+=point_size)
        {
            //  if(map[i+window_start_x][j+window_start_y] == true)
            int m = int(window_center_x + i/point_size);
            int n = int(window_center_y + j/point_size);
            
            if(map[m][n] == true)
            {
                glVertex2f(i,j);
                // std::cout << "MAP (x,y):" << m << " " << n << std::endl;
                // std::cout << "WINDOW (x,y):" << i << " " << j << std::endl;

                // std::cout << i << " " << j <<std::endl;
            }
        }
    }
    glEnd();
    if(update_map_flag == 1)
    {
        std::cout <<"update MAP: "<< update_map_flag << std::endl;
        upedateMap();
        current_map_state = 1;
    }
    else
    {
        current_map_state = 0;
    }
    // upedateMap();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    draw_mesh();
    draw_map();
    glFlush();
}




void OnTimer(int value)
{
    // upedateMap();
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, OnTimer, 1);
}

int middle_up_x, middle_up_y;
static int middle_down_x, middle_down_y;

void OnMouse(int button,int state,int x,int y)
{
    
    
    //将鼠标坐标装换为左下角为
    int i = x / point_size;
    int j = (WINDOW_HEIGHT - y) / point_size;
    //讲鼠标坐标映射到map坐标系
    int m = i - WINDOW_WIDTH / 2 / point_size + window_center_x;
    int n = j - WINDOW_HEIGHT / 2 / point_size + window_center_y;

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        map[m][n] = true;
        left_down_flag = 1;
        // std::cout << "MOUSE LEFT DOWN:(" << x << " " << y << ")" << std::endl;
    }
    else
    {
        left_down_flag = 0;
    }

    /*右键事件处理 */
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        map[m][n] = false;
        right_down_flag = 1;
        std::cout << i << " " << j << std::endl;
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
        middle_down_x = i;
        middle_down_y = j;
        window_center_old_x = window_center_x;
        window_center_old_y = window_center_y;

        
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
        (zoom >= 0.5)? zoom-=0.1 : zoom = 0.4;
        point_size = POINT_SIZE * zoom;
        mesh_size = MESH_SIZE * zoom;
        // std::cout << zoom << std::endl;
    }
    
    

}

void OnMotion(int x, int y)
{
    int i = x / point_size;
    int j = (WINDOW_HEIGHT - y) / point_size;
    int m = i - WINDOW_WIDTH/2/point_size+window_center_x;
    int n = j - WINDOW_HEIGHT/2/point_size+window_center_y;

    if(left_down_flag == 1)
    {
        map[m][n] = true;
        // std::cout << "MOUSE LEFT DOWN:(" << x << " " << y << ")" << std::endl;
    }
    if(right_down_flag == 1)
    {
        map[m][n] = false;
    }
    if(middle_down_flag == 1)
    {
        std::cout << "WHEEL UP:" << i << " " << j << std::endl;
        //middle_down_flag = 0;
        middle_up_x = i;
        middle_up_y = j;
        offset_x = middle_up_x - middle_down_x;
        offset_y = middle_up_y - middle_down_y;
        window_center_x = window_center_old_x - offset_x;
        window_center_y = window_center_old_y - offset_y;
        std::cout << "OFFESET XY:" << offset_x << " " << offset_y << std::endl;
        std::cout << "CENTER XY:" << window_center_x << " " << window_center_y << std::endl;

        //限幅处理
        if(window_center_x + WINDOW_WIDTH/point_size/2 >= WIDTH)
        {
            window_center_x = WIDTH - WINDOW_WIDTH/point_size/2;
        }
        if(window_center_x - WINDOW_WIDTH/point_size/2 <= 0)
        {
            window_center_x = WINDOW_WIDTH/point_size/2;
        }
        if(window_center_y + WINDOW_HEIGHT/point_size/2 >= HEIGHT)
        {
            window_center_y = HEIGHT - WINDOW_HEIGHT/point_size/2;
        }
        if(window_center_y - WINDOW_HEIGHT/point_size/2 <= 0)
        {
            window_center_y = WINDOW_HEIGHT/point_size/2;
        }

    }
    
}

void keyboard(unsigned char key, int x, int y)
{
    if(key == ' ' )
    {
        
        if(current_map_state == 1)
        {
            update_map_flag = 0;
            std::cout << "KEY:" << key << " "  << update_map_flag <<  std::endl;
        }
        if(current_map_state == 0)
        {
            update_map_flag = 1;
            std::cout << "KEY:" << key << " "  << update_map_flag <<  std::endl;
        }
    }
    
}

void init(void)
{
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

int main(int argc, char *argv[])
{
    map[200][150] = true;
    map[51][50] = true;
    map[52][50] = true;
    map[52][51] = true;
    map[51][52] = true;

        // map[50][50] = true;
    // map[50][49] = true;
    // map[50][48] = true;
    // map[51][48] = true;
    // map[49][52] = true;

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
    init();

    // std::cout << glutGet(GLUT_WINDOW_WIDTH) << " " << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;
    // std::cout << glutGet(GLUT_SCREEN_WIDTH) << " " << glutGet(GLUT_SCREEN_HEIGHT) << std::endl;
    glutMouseFunc(&OnMouse);
    glutMotionFunc(&OnMotion);
    glutKeyboardFunc(&keyboard);
    glutDisplayFunc(&display);
    glutTimerFunc(1000/FPS, &OnTimer,1);
    glutMainLoop();
    return 0;
}