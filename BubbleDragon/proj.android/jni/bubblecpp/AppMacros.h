#ifndef __AppMacros_H__
#define __AppMacros_H__

#include "cocos2d.h"

#define ARRAYSIZE 14						//泡泡数组行数
#define ARRAYCOL 9							//泡泡数组列数
#define BACKGROUND_LEVEL 0					//游戏背景的宏
#define MENU_LEVEL 10						//游戏菜单的宏
#define DJ_LEVEL 30
#define GAME_LEVEL 20						//游戏层的宏
#define DASHBOARD_LEVEL 30
#define GAME_STOP_LEVEL 40					//游戏结束的宏
#define GKHONE 1							//关卡1的宏
#define GKHTWO 2							//关卡2的宏
#define GKHTHREE 3							//关卡3的宏

#define PI 3.14159265						//π的宏
#define MAX_VALUE (3.4028235*pow(10,38))	//定义一个最大浮点数的宏

#define CBX_INIT 270						//发射泡泡的横坐标的宏
#define CBY_INIT 140						//发射泡泡的纵坐标的宏

#define R 30								//泡泡半径

#define DR (2*R)							//泡泡直径

#define R3S ((float)sqrt(3)*R)				//泡泡半径的根号3倍的宏
#define SPEED 400							//泡泡发射速度
#define GOTAG 11							//游戏结束时创建的精灵tag值
#define RMTAG 21							//游戏继续时创建的精灵tag值

/**
 * @author zhenyu_lu
 * 三关游戏泡泡的布局二维数组
 * {@code .h}
 * */
int GKONE[ARRAYSIZE][ARRAYCOL]=
{
    0,6,5,4,4,5,6,5,0,
    0,6,5,3,3,5,6,6,0,
    0,6,5,5,5,5,6,7,8,
    0,6,6,6,6,6,6,0,0,
    1,2,3,4,5,6,7,8,1,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0
};
int GKTWO[ARRAYSIZE][ARRAYCOL]=
{
    0,0,1,1,1,1,1,0,0,
    0,0,1,0,0,5,1,1,0,
    0,0,1,0,0,0,0,1,8,
    0,1,1,1,1,1,1,1,0,
    0,3,5,0,6,0,8,4,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0
};
int GKTHREE[ARRAYSIZE][ARRAYCOL]=
{
    0,2,3,4,5,6,7,8,0,
    0,0,6,0,4,3,2,1,0,
    0,0,0,5,0,6,7,8,0,
    0,0,0,5,0,0,8,1,0,
    1,2,3,4,0,0,8,8,1,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0
};


#endif