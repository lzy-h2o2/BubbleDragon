#include "AppDelegate.h"
#include "ShootBubbleSceneManager.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"

USING_NS_CC;

/**
 * @author zhenyu_lu
 * 实现整个程序在运行、前台、后台的操作
 * {@code c++}
 * */
AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

//初始化方法
bool AppDelegate::applicationDidFinishLaunching()
{
    //获取导演
    auto director = Director::getInstance();
    //获取绘制用GLView
    auto glview = director->getOpenGLView();
    //若不存在glview则重新创建
    if(!glview)
    {
         glview = GLView::create("Test Cpp");
    }
    //设置绘制用GLView
    director->setOpenGLView(glview);
    //设置目标分辨率,别的分辨率的屏幕将自动上下或左右留白进行多分辨率自适应
    glview->setDesignResolutionSize(540,960, ResolutionPolicy::SHOW_ALL);
	//设置为显示FPS等信息
    //director->setDisplayStats(true);
    //系统模拟时间间隔
    //director->setAnimationInterval(1.0 / 60);
    //创建欢迎场景
    ShootBubbleSceneManager* sbsm = new ShootBubbleSceneManager();
    sbsm->createScene();
    //切换到欢迎场景显示
    director->runWithScene(sbsm->mainScene);
    return true;
}

//当程序进入后台时调用此方法
void AppDelegate::applicationDidEnterBackground()
{
	//停止动画
    Director::getInstance()->stopAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

//当程序进入前台时调用
void AppDelegate::applicationWillEnterForeground()
{
	//开始动画
    Director::getInstance()->startAnimation();
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
