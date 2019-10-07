#include <GL/glut.h>
#include "life_game.hpp"
#include <iostream>
#include "draw.h"
#include "point.h"

/*
 * g++ draw_window.cpp -o draw_window -lGL -lGLU -lglut
 * 编译时一定要加上-lGL -lGLU -lglut 否则会出现no reference的错误
 */


// float point_size = POINT_SIZE;
// float mesh_size = MESH_SIZE;
// float zoom  = 1;

// bool left_down_flag = 0;
// bool right_down_flag = 0;
// bool middle_down_flag = 0;
// int offset_x = 0;
// int offset_y = 0;
// int window_center_x = WIDTH / 2;
// int window_center_y = HEIGHT / 2;
// int window_center_old_x = window_center_x;
// int window_center_old_y = window_center_y;
// bool update_map_flag = 0;
// bool current_map_state = 0;
// LifeGame lifegame;


Draw::Draw()
{
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
    // for(float i = -WINDOW_WIDTH/2 ; i < WINDOW_WIDTH/2; i += point_size)
    // {
    //     for(float j = -WINDOW_HEIGHT/2  ; j < WINDOW_HEIGHT/2; j+=point_size)
    //     {
    //         //将点从窗口像素坐标系映射到map坐标系
    //         Point tmp;
    //         tmp.x = int(window_center.x + i /point_size);
    //         tmp.y = int(window_center.y + j /point_size);
            
    //         if(LifeGame::getMapStatus(tmp) == true)
    //         {
    //             glVertex2f(i,j);
    //         }
    //     }
    // }
    //第一象限
    for(float i = point_size/2 ; i < WINDOW_WIDTH/2; i += point_size)
    {
        for(float j = point_size/2  ; j < WINDOW_HEIGHT/2; j+=point_size)
        {
            //将点从窗口像素坐标系映射到map坐标系
            Point tmp;
            tmp.x = int(window_center.x + i /point_size);
            tmp.y = int(window_center.y + j /point_size);
            
            if(LifeGame::getMapStatus(tmp) == true)
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
            
            if(LifeGame::getMapStatus(tmp) == true)
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
            
            if(LifeGame::getMapStatus(tmp) == true)
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
            
            if(LifeGame::getMapStatus(tmp) == true)
            {
                glVertex2f(i,j);
            }
        }
    }
    glEnd();

    if(map_update_flag == 1)
    {
        LifeGame::iteration();
        map_current_status = 1;
    }
    else
    {
        map_current_status = 0;
    }
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
        LifeGame::setMapStatus(m,n,true);
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
        LifeGame::setMapStatus(m,n,false);
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
        LifeGame::setMapStatus(m, n, true);
        // std::cout << "MOUSE LEFT DOWN:(" << x << " " << y << ")" << std::endl;
    }
    if(right_down_flag == 1)
    {
        LifeGame::setMapStatus(m, n, false);
    }
    if(middle_down_flag == 1)
    {
        std::cout << "WHEEL UP:" << i << " " << j << std::endl;
        //middle_down_flag = 0;
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

// void draw_mesh(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT);
//     glColor3f(0.10, 0.10, 0.10);
//     glBegin(GL_LINES);
//     //横向
//     for(int i = -WINDOW_HEIGHT/2 + mesh_size/2; i <= WINDOW_HEIGHT/2; i += mesh_size)
//     {
//         glVertex2f(-WINDOW_WIDTH/2, i);
//         glVertex2f(WINDOW_WIDTH/2, i);
//     }
//     //纵向
//     for(int i = -WINDOW_WIDTH/2 + mesh_size/2; i <= WINDOW_WIDTH/2; i += mesh_size)
//     {
//         glVertex2f(i, -WINDOW_HEIGHT/2);
//         glVertex2f(i, WINDOW_HEIGHT/2);
//     }
//     glEnd();
// }

// void draw_map(void)
// {
//     point_size = POINT_SIZE * zoom;
//     glPointSize(point_size);
//     glColor3f(1.0, 1.0, 1.0);
//     glBegin(GL_POINTS);
//     // glVertex2i(0,0);
//     // std::cout<< "Point Size:" << point_size << std::endl;
//     for(int i = -WINDOW_WIDTH/2; i < WINDOW_WIDTH/2; i += point_size)
//     {
//         for(int j = -WINDOW_HEIGHT/2; j < WINDOW_HEIGHT/2; j+=point_size)
//         {
//             //  if(map[i+window_start_x][j+window_start_y] == true)
//             int m = int(window_center_x + i/point_size);
//             int n = int(window_center_y + j/point_size);
            
//             if(lifegame.map[m][n] == true)
//             {
//                 glVertex2f(i,j);
//                 // std::cout << "MAP (x,y):" << m << " " << n << std::endl;
//                 // std::cout << "WINDOW (x,y):" << i << " " << j << std::endl;

//                 // std::cout << i << " " << j <<std::endl;
//             }
//         }
//     }
//     glEnd();
//     if(update_map_flag == 1)
//     {
//         std::cout <<"update MAP: "<< update_map_flag << std::endl;
//         lifegame.updateMap();
//         current_map_state = 1;
//     }
//     else
//     {
//         current_map_state = 0;
//     }
//     // upedateMap();
// }

// void display(void)
// {
//     glClear(GL_COLOR_BUFFER_BIT);
    
//     draw_mesh();
//     draw_map();
//     glFlush();
// }




// void OnTimer(int value)
// {
//     glutPostRedisplay();
//     glutTimerFunc(1000/FPS, OnTimer, 1);
// }

// int middle_up_x, middle_up_y;
// static int middle_down_x, middle_down_y;

// void OnMouse(int button,int state,int x,int y)
// {
//     //将鼠标坐标装换为左下角为
//     int i = x / point_size;
//     int j = (WINDOW_HEIGHT - y) / point_size;
//     //讲鼠标坐标映射到map坐标系
//     int m = i - WINDOW_WIDTH / 2 / point_size + window_center_x;
//     int n = j - WINDOW_HEIGHT / 2 / point_size + window_center_y;

//     if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//     {
//         lifegame.map[m][n] = true;
//         left_down_flag = 1;
//         // std::cout << "MOUSE LEFT DOWN:(" << x << " " << y << ")" << std::endl;
//     }
//     else
//     {
//         left_down_flag = 0;
//     }

//     /*右键事件处理 */
//     if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
//     {
//         lifegame.map[m][n] = false;
//         right_down_flag = 1;
//         std::cout << i << " " << j << std::endl;
//     }
//     else
//     {
//         right_down_flag = 0;
//     }

//     /*滚轮按下事件处理 */
//     if(button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
//     {
//         std::cout << "WHEEL DOWN" << i << " " << j <<  std::endl;
//         middle_down_flag = 1;
//         middle_down_x = i;
//         middle_down_y = j;
//         window_center_old_x = window_center_x;
//         window_center_old_y = window_center_y;       
//     }
//     else
//     {
//         middle_down_flag = 0;      
//     }  
    
//     if(button == GLUT_WHEEL_UP && state == GLUT_UP)
//     {
//         (zoom <= 5)? zoom+=0.1 : zoom = 5.1;
//         point_size = POINT_SIZE * zoom;
//         mesh_size = MESH_SIZE * zoom;
//         // std::cout << zoom << std::endl;
//     }
//     if(button == GLUT_WHEEL_DOWN && state == GLUT_DOWN)
//     {
//         (zoom >= 0.5)? zoom-=0.1 : zoom = 0.4;
//         point_size = POINT_SIZE * zoom;
//         mesh_size = MESH_SIZE * zoom;
//         // std::cout << zoom << std::endl;
//     }   
// }

// void OnMotion(int x, int y)
// {
//     int i = x / point_size;
//     int j = (WINDOW_HEIGHT - y) / point_size;
//     int m = i - WINDOW_WIDTH/2/point_size+window_center_x;
//     int n = j - WINDOW_HEIGHT/2/point_size+window_center_y;

//     if(left_down_flag == 1)
//     {
//         lifegame.map[m][n] = true;
//         // std::cout << "MOUSE LEFT DOWN:(" << x << " " << y << ")" << std::endl;
//     }
//     if(right_down_flag == 1)
//     {
//         lifegame.map[m][n] = false;
//     }
//     if(middle_down_flag == 1)
//     {
//         std::cout << "WHEEL UP:" << i << " " << j << std::endl;
//         //middle_down_flag = 0;
//         middle_up_x = i;
//         middle_up_y = j;
//         offset_x = middle_up_x - middle_down_x;
//         offset_y = middle_up_y - middle_down_y;
//         window_center_x = window_center_old_x - offset_x;
//         window_center_y = window_center_old_y - offset_y;
//         std::cout << "OFFESET XY:" << offset_x << " " << offset_y << std::endl;
//         std::cout << "CENTER XY:" << window_center_x << " " << window_center_y << std::endl;

//         //限幅处理
//         if(window_center_x + WINDOW_WIDTH/point_size/2 >= WIDTH)
//         {
//             window_center_x = WIDTH - WINDOW_WIDTH/point_size/2;
//         }
//         if(window_center_x - WINDOW_WIDTH/point_size/2 <= 0)
//         {
//             window_center_x = WINDOW_WIDTH/point_size/2;
//         }
//         if(window_center_y + WINDOW_HEIGHT/point_size/2 >= HEIGHT)
//         {
//             window_center_y = HEIGHT - WINDOW_HEIGHT/point_size/2;
//         }
//         if(window_center_y - WINDOW_HEIGHT/point_size/2 <= 0)
//         {
//             window_center_y = WINDOW_HEIGHT/point_size/2;
//         }

//     }
    
// }

// void keyboard(unsigned char key, int x, int y)
// {
//     if(key == ' ' )
//     {
        
//         if(current_map_state == 1)
//         {
//             update_map_flag = 0;
//             std::cout << "KEY:" << key << " "  << update_map_flag <<  std::endl;
//         }
//         if(current_map_state == 0)
//         {
//             update_map_flag = 1;
//             std::cout << "KEY:" << key << " "  << update_map_flag <<  std::endl;
//         }
//     }
    
// }



// int main(int argc, char *argv[])
// {
//     glutInit(&argc, argv);
//     /*窗口使用单焕存，并且使用RGB颜色模型 */
//     glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//     /*设置窗口左上角的位置 */
//     glutInitWindowPosition(500, 200);
//     /*设置窗口的宽高 */
//     glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//     /*创建窗口，传入参数为窗口标题 */
//     glutCreateWindow("Life Game");
//     /*初始化OpenGL配置 */
//     init();

//     // std::cout << glutGet(GLUT_WINDOW_WIDTH) << " " << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;
//     // std::cout << glutGet(GLUT_SCREEN_WIDTH) << " " << glutGet(GLUT_SCREEN_HEIGHT) << std::endl;
//     glutMouseFunc(&OnMouse);
//     glutMotionFunc(&OnMotion);
//     glutKeyboardFunc(&keyboard);
//     glutDisplayFunc(&display);
//     glutTimerFunc(1000/FPS, &OnTimer,1);
//     glutMainLoop();
//     return 0;
// }