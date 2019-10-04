#include <iostream>
#include "life_game.hpp"

bool LifeGame::map[WIDTH][HEIGHT] = {0};

LifeGame::LifeGame()
{

}

LifeGame::~LifeGame()
{

}

void LifeGame::setMapStatus(Point point, bool status)
{
    map[point.x][point.y] = status;
}

void LifeGame::setMapStatus(int x, int y, bool status)
{
    map[x][y] = status;
}

bool LifeGame::getMapStatus(Point point)
{
    return map[point.x][point.y];
}

bool LifeGame::getMapStatus(int x, int y)
{
    return map[x][y];
}

//该函数不能计算边界点周围点的数量
int LifeGame::getNumAround(Point point)
{
    int cnt = 0;

    for(int i = point.x - 1; i <= point.x + 1; ++i)
    {
        for(int j = point.y - 1; j <= point.y + 1; ++j)
        {
            if(map[i][j] == true)
            {
                cnt++;
            }
        }
    }
    if(map[point.x][point.y] == true)
    {
        cnt -= 1;
    }
    return cnt;
}

bool LifeGame::survivalRule(Point point)
{

    int sum = getNumAround(point);
    bool res = false;
    if(sum < 2 || sum >3)
    {
        res = false;
    }
    else if (sum == 3)
    {
        res = true;
    }
    else if(sum == 2)
    {
        res = map[point.x][point.y];
    }
    return res;
}

void LifeGame::iteration(void)
{
    Point tmp_point;
    bool tmp_map[WIDTH][HEIGHT] = {0};

    //根据生命游戏规则将计算结果存入临时地图
    for(tmp_point.x = 1; tmp_point.x < WIDTH - 1; ++tmp_point.x)
    {
        for(tmp_point.y = 1; tmp_point.y < HEIGHT - 1; ++tmp_point.y)
        {
            tmp_map[tmp_point.x][tmp_point.y] = survivalRule(tmp_point);
        }
    }

    for(int i = 0; i < WIDTH; i++)
    {
        for(int j = 0; j < HEIGHT; j++)
        {
            map[i][j] = tmp_map[i][j];
        }
    }
}
