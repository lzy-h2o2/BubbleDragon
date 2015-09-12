#ifndef _HELPLAYER_H
#define _HELPLAYER_H
#include "cocos2d.h"
#include "ShootBubbleSceneManager.h"
using namespace cocos2d;

/**
 * @author zhenyu_lu
 * HelpLayer 帮助布景定义
 * {@code .h}
 * */

class HelpLayer :public Layer
{
    public:
		//初始化布景方法
    virtual bool init();
//    声明一个指向场景管理器的指针
    ShootBubbleSceneManager *sbsm;
//    声明背景和帮助图片精灵
    Sprite *bg;
    Sprite *helpOne;
    Sprite *helpTwo;
    MenuItemImage* prev;
    MenuItemImage* next;
    //记录当前所在页面的索引
    int ms=1;
//    点击返回、上一页、下一页按钮时被回调的方法
    void backCallback();
    void nextCallback();
    void prevCallback();
    void setMenuEnable();
	CREATE_FUNC(HelpLayer);
};

#endif
