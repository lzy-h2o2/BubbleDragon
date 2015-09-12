#ifndef __ChooseGK_H_
#define __ChooseGK_H_
#include "ShootBubbleSceneManager.h"
using namespace cocos2d;
class ChooseGKLayer : public Layer
{
public:
	bool init();					//初始化布景
    ShootBubbleSceneManager *sbsm;	//声明指向场景管理器的指针
    Sprite*(sp) [4];    			//声明“关卡选择”四个字的数组图片精灵
    void GKCallbackone();			//声明关卡1的回调
    void GKCallbacktwo();			//声明关卡2的回调
    void GKCallbackthree();			//声明关卡3的回调
    void backCallback();			//声明关“返回”的回调
    CREATE_FUNC(ChooseGKLayer);		//定义回调宏
    static int gk;					//定义当前选择的关卡
};
#endif
