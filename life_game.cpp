#include <iostream>
#include "life_game.hpp"
#include "map.h"


LifeGame::LifeGame()
{

}

LifeGame::~LifeGame()
{

}

//该函数不能计算边界点周围点的数量
int LifeGame::getNumAround(Map & map, Point point)
{
    int cnt = 0;

    for(int i = point.x - 1; i <= point.x + 1; ++i)
    {
        for(int j = point.y - 1; j <= point.y + 1; ++j)
        {
            // if(map[i][j] == true)
            if(map.getValue(i,j) == true)
            {
                cnt++;
            }
        }
    }
    // if(map[point.x][point.y] == true)
    if(map.getValue(point) == true)
    {
        cnt -= 1;
    }
    return cnt;
}

bool LifeGame::survivalRule(Map &map, Point point)
{

    int sum = getNumAround(map, point);
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
        // res = map[point.x][point.y];
        res = map.getValue(point);
    }
    return res;
}

void LifeGame::iteration(Map &map)
{
    Point tmp_point;
    Map tmp_map;

    //根据生命游戏规则将计算结果存入临时地图
    for(tmp_point.x = 1; tmp_point.x < tmp_map.getWidth() - 1; ++tmp_point.x)
    {
        for(tmp_point.y = 1; tmp_point.y < tmp_map.getHeight() - 1; ++tmp_point.y)
        {
            tmp_map.setValue(tmp_point, survivalRule(map, tmp_point));
        }
    }

    for(int i = 0; i < map.getWidth(); i++)
    {
        for(int j = 0; j < map.getHeight(); j++)
        {
            map.setValue(i,j,tmp_map.getValue(i, j));
        }
    }
}
