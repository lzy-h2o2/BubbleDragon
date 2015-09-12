#ifndef __StartLayer_H__
#define __StartLayer_H__
#include "cocos2d.h"
#include "ShootBubbleSceneManager.h"

using namespace cocos2d;

/**
 * @author zhenyu_lu
 * StartLayer 程序启动加载动画和菜单布景定义
 * {@code .h}
 * */

class StartLayer: public Layer
{
public:
	Size visibleSize;
	Point origin;
//	初始化布景
	virtual bool init();
    void initSound();
    //    加载完成一副图片时回调的方法
    void loadingCallBack(Texture2D* tt);
    //	异步加载的方法
	void loadingTexturesAsync();
    //    点击开始游戏时被回调的方法
    void startCallback();
    //    点击声音按钮时被回调的方法
    void soundCallback();
    //    点击帮助按钮时被回调的方法
    void helpCallback();
    //    点击关于按钮时被回调的方法
    void aboutCallback();
    //    点击排行榜按钮时被回调的方法
    void phbCallback();
    //	      关闭菜单回调方法
    void menuCloseCallback(cocos2d::Ref* pSender);
public:
//    声明一个指向场景管理器对象的指针
		ShootBubbleSceneManager *sbsm;
//    声明一个一个bool变量，用于是否播放声音
       static bool soundB;
//    声明一个int变量，用于记录是否将资源异步加载完全
		int jd=0;
//    声明一个用于加载图片资源时显示的精灵
		Sprite* loadingPic;
		Sprite* logoPic;
        Label* lPros;
//    声明一个指向菜单项的指针
        MenuItemImage* soundon;
        MenuItemImage* soundoff;

    //Cocos2d-x中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
	CREATE_FUNC(StartLayer);
};
#endif
