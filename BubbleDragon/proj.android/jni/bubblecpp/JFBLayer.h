#ifndef __ShootBubble__JFBLayer__
#define __ShootBubble__JFBLayer__

#include "cocos2d.h"
#include "ShootBubbleSceneManager.h"
using namespace cocos2d;

/**
 * @author zhenyu_lu
 * JFBLayer 排行布景定义
 * {@code .h}
 * */

class JFBLayer :public Layer
{
public:
    //初始化布景方法
    virtual bool init();
    //    声明一个指向场景管理器的指针
    ShootBubbleSceneManager *sbsm;
    //	声明用于存储游戏用时的五个标签
    Label*(no) [5];
    int currGK=1;
    void getScore(int gk);
    void prevCallback();
    void nextCallback();
    //    点击返回按钮时被回调的方法
    void backCallback();
    void resetScore();
    CREATE_FUNC(JFBLayer);
};
#endif /* defined(__ShootBubble__JFBLayer__) */
