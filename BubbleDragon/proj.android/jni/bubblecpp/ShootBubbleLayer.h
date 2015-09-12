#ifndef __ShootBubbleLayer_H__
#define __ShootBubbleLayer_H__

#include "cocos2d.h"
#include "vector"
#include "math.h"
#include "ShootBubbleSceneManager.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
USING_NS_CC_EXT;

/**
 * @author zhenyu_lu
 * ShootBubbleLayer 游戏射击主界面布景定义
 * {@code .h}
 * */

class ShootBubbleLayer : public Layer
{
public:
	//初始化的方法
	virtual bool init();
	ShootBubbleSceneManager *sbsm;
	Size visibleSize;
	Point origin;
    bool isPause=false;
    NodeGrid* effectGrid;
    Sprite* bg;
	LabelAtlas* FSLabel;
	Label *tipLabel;
	int timeScore=-1;
    Sprite* pSprite;
    Label*(no) [5];
	//压柱
	Sprite* compressor;
	Sprite* compressor1;
	Sprite* compressor2;
	Scale9Sprite* compressor_bodyL;
	Scale9Sprite* compressor_bodyR;
	//弹膛精灵
	Sprite* launcher;
	Sprite* ballStart;
	Sprite* ballNextStart;
	Point bLocation[14][9];
	int IsEmpty[14][9];
	int IsEmptyTemp[14][9];
	int Goneball[14][9];
	float MAXHeight=850.0;
	bool IsGameOver=false;
	int shootBallColor=0;
	int currBallColor=0;
	int nextBallColor=0;
	int Row=0;
	int Col=0;
    int maxRow=0;
	float cbx;
	float cby;
	//碰撞时发射球球心坐标
	float cbpx=0;
	float cbpy=0;
	std::vector<Point>* path;
	std::vector<Sprite*>* allBall;
	std::vector<Point>* RMball;
	//当前发射方向
	float direction=0;
	//发射时的速度向量，仅表示方向，模为1
	float vx;
	float vy;
	//球碰撞的最小距离
	float minJLBall;
    float xRight;
    float yRight;
    float xUp;
    float yUp;
    float xLeft;
    float yLeft;
	int RMCountballs=1;
	bool moveFlag=false;
	void intiBall();
	void initLocation();
	void initIsEmpty();
	void drawBall();
	void addBall();
	//消除泡泡
	void moveFlagCallback();
    void puaseCallback();
	//开始单点触控事件的处理方法
	bool onTouchBegan(Touch* touch, Event* event);
	void shootBall(Point location);
	//计算球运行路径
	void calPath();
	//判断能否碰到地图里面的泡泡
	bool calEndBall();
	Point calCenter(int row,int col);
	float distance(float A,float B,float C,float x,float y);
	void search(int row,int col);
	void copyIsEmpty();
	void copyIsEmptyTemp();
	bool searchRoad(int row,int col);
	void ballFalling(int row,int  col,int LR);
	void ballFalled();
	void update();
	void updateLocation();
    bool gameStopCallback();
    void menuStopCallback();
    void menuStartCallback();
    void removeNodeGird();
    void gameRestartFUNC();
    void updatetime();
    void phbMenu();
    float callDisR();
    float callDisU();
    float callDisL();
    void RMballDY3();
    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(ShootBubbleLayer);
};

#endif
