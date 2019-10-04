#include "life_game.hpp"
#include "draw.h"

LifeGame lifegame;
Draw draw;

void onTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, onTimer, 1);
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

void callOnMouse(int button,int state,int x,int y)
{
    draw.onMouse( button, state, x, y);
}
void callOnMotion(int x, int y)
{
    draw.onMotion(x, y);
}
void callDisplay(void)
{
    draw.display();
}
void callKeyboard(unsigned char key, int x, int y)
{
    draw.keyboard(key, x, y);
}

int main(int argc, char *argv[])
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
    init();

    // std::cout << glutGet(GLUT_WINDOW_WIDTH) << " " << glutGet(GLUT_WINDOW_HEIGHT) << std::endl;
    // std::cout << glutGet(GLUT_SCREEN_WIDTH) << " " << glutGet(GLUT_SCREEN_HEIGHT) << std::endl;
    glutMouseFunc(&callOnMouse);
    glutMotionFunc(&callOnMotion);
    glutKeyboardFunc(&callKeyboard);
    glutDisplayFunc(&callDisplay);
    glutTimerFunc(1000/FPS, &onTimer,1);
    glutMainLoop();
    return 0;
}