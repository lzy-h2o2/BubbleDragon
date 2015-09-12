#ifndef __ShootBubble__AboutUSLayer__
#define __ShootBubble__AboutUSLayer__

#include <iostream>
#include "cocos2d.h"
#include "ShootBubbleSceneManager.h"

/**
 * @author zhenyu_lu
 * AboutUSLayer 关于布景
 * {@code .h}
 * */
using namespace cocos2d;
class AboutUSLayer :public Layer
{
public:
	//初始化布景
	virtual bool init();
	//声明指向场景管理器的指针
    ShootBubbleSceneManager *sbsm;
    //返回键的回调
    void backCallback();
    CREATE_FUNC(AboutUSLayer);
};
#endif
