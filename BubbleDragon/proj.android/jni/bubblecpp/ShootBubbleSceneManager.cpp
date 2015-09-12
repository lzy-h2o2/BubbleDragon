#include "ShootBubbleSceneManager.h"
#include "ShootBubbleLayer.h"
#include "StartLayer.h"
#include "HelpLayer.h"
#include "ChooseGKLayer.h"
#include "AboutUSLayer.h"
#include "JFBLayer.h"
using namespace cocos2d;

/**
 * @author zhenyu_lu
 * ShootBubbleSceneManager 主菜单
 * {@code c++}
 * */

//创建第一进入游戏场景
Scene* ShootBubbleSceneManager::createScene()
{
    //创建一个场景对象
    mainScene = Scene::create();
    //创建一个布景对象
    auto mlayer = StartLayer::create();
    mlayer->sbsm=this;
    //将布景添加到场景中
    mainScene->addChild(mlayer);
    //返回主场景
    return mainScene;
}
//切换到游戏场景的方法
void ShootBubbleSceneManager::goGameScene()
{
//    设置深度检测
	Director::getInstance()->setDepthTest(true);
//    创建一个场景对象
	gameScene = Scene::create();
//    创建一个布景对象
	ShootBubbleLayer* glayer = ShootBubbleLayer::create();
    glayer->sbsm=this;
//    将布景对象添加到场景中
	gameScene->addChild(glayer);
//    创建一个切换场景到特效
    auto ss=TransitionProgressInOut::create(1, gameScene);
//    切换到游戏场景
	Director::getInstance()->replaceScene(ss);
}
//切换到主场景的方法
void ShootBubbleSceneManager::goMainScene()
{
    //    设置深度检测
	Director::getInstance()->setDepthTest(true);
    //    创建一个场景对象
	mainScene = Scene::create();
    //    创建一个布景对象
	auto mlayer = StartLayer::create();
	mlayer->sbsm=this;
    //    将布景对象添加到场景中
	mainScene->addChild(mlayer);
    //    创建一个切换场景到特效
    auto ss=TransitionProgressInOut::create(1, mainScene);
    if(StartLayer::soundB)
   {
       CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
   }
    else
    {
    	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_scene_bg.mp3",true);
    }
    //    切换到主场景
	Director::getInstance()->replaceScene(ss);
}
//切换到帮助场景的方法
void ShootBubbleSceneManager::gohelpScene()
{
//    设置深度检测
	Director::getInstance()->setDepthTest(true);
//    创建一个场景对象
	helpScene = Scene::create();
//    创建一个布景对象
	HelpLayer* hlayer = HelpLayer::create();
	hlayer->sbsm=this;
//    将布景对象添加到场景中
	helpScene->addChild(hlayer);
//    创建一个切换场景到特效
    auto ss=TransitionProgressOutIn::create(1, helpScene);
//    切换到帮助场景
	Director::getInstance()->replaceScene(ss);
}
//切换到主场景的方法
void ShootBubbleSceneManager::goGKScene()
{
//    设置深度检测
	Director::getInstance()->setDepthTest(true);
//    创建一个场景对象
	GKScene = Scene::create();
//    创建一个布景对象
	auto clayer = ChooseGKLayer::create();
	clayer->sbsm=this;
//    将布景对象添加到场景中
	GKScene->addChild(clayer);
//    创建一个切换场景到特效
    auto ss=TransitionProgressOutIn::create(1, GKScene);
//    切换到帮助场景
	Director::getInstance()->replaceScene(ss);
}
//切换到主场景的方法
void ShootBubbleSceneManager::goAboutUSScene()
{
//    设置深度检测
	Director::getInstance()->setDepthTest(true);
    //    创建一个场景对象
	AboutUSScene = Scene::create();
    //    创建一个布景对象
	auto alayer = AboutUSLayer::create();
	alayer->sbsm=this;
    //    将布景对象添加到场景中
	AboutUSScene->addChild(alayer);
//    创建一个切换场景到特效
    auto ss=TransitionProgressOutIn::create(1, AboutUSScene);
    //    切换到帮助场景
	Director::getInstance()->replaceScene(ss);
}
//切换到主场景的方法
void ShootBubbleSceneManager::goJbfScene()
{
    //    设置深度检测
	Director::getInstance()->setDepthTest(true);
    //    创建一个场景对象
	JbfScene = Scene::create();
    //    创建一个布景对象
	auto jlayer = JFBLayer::create();
	jlayer->sbsm=this;
    //    将布景对象添加到场景中
	JbfScene->addChild(jlayer);
    //    创建一个切换场景到特效
    auto ss=TransitionProgressOutIn::create(1, JbfScene);
    //    切换到帮助场景
	Director::getInstance()->replaceScene(ss);
}
