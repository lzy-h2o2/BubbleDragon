#ifndef __ShootBubbleSceneManager_H__
#define __ShootBubbleSceneManager_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
using namespace cocos2d;

/**
 * @author zhenyu_lu
 * ShootBubbleSceneManager 主菜单定义
 * {@code .h}
 * */

class ShootBubbleSceneManager
{
public:
	//创建第一次进入游戏的场景
    Scene* createScene();

//    声明指向不同场景对象的指针
    Scene* mainScene;
    Scene* gameScene;
    Scene* helpScene;
    Scene* GKScene;
    Scene* AboutUSScene;
    Scene* JbfScene;
    
    //切换到游戏场景到方法
    void goGameScene();
    //切换到主场景到方法
	void goMainScene();
    //切换到帮助场景到方法
    void gohelpScene();
    //切换到选关场景到方法
    void goGKScene();
    //切换到关于场景到方法
    void goAboutUSScene();
    void goJbfScene();
};

#endif
