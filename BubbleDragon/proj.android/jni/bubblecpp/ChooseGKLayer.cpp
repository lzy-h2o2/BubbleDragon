#include "ChooseGKLayer.h"
#include "ShootBubbleLayer.h"
#include <iostream>
#include "cocos2d.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"

/**
 * @author zhenyu_lu
 * ChooseGKLayer 关卡布景
 * {@code c++}
 * */

//初始化关卡计数器
int ChooseGKLayer::gk=0;

bool ChooseGKLayer::init()
{ //调用父类的初始化方法
	if (!Layer::init())
	{
		return false;
	}
//    创建一个背景
    Sprite* bgSprite= Sprite::create("mainpic/bg.png");
//    设置其位置
    bgSprite->setPosition(Point(270,480));
//    将其添加到布景中
    this->addChild(bgSprite);
    
    Sprite* sppl = Sprite::create("mainpic/menu_title.png");
    sppl->setPosition(Point(270,800));
    this->addChild(sppl,2);
    ParticleSystemQuad* psq = ParticleSystemQuad::create("lzxt/stars.plist");
    psq->setBlendAdditive(true);
    this->addChild(psq, 10);
    psq->setPosition( Point( 270, 800) );
    
    sp[0]=Sprite::create("mainpic/guan.png");
    sp[0]->setPosition(Point(80,560));
    this->addChild(sp[0]);
    sp[1]=Sprite::create("mainpic/ka.png");
    sp[1]->setPosition(Point(200,560));
    this->addChild(sp[1]);
    sp[2]=Sprite::create("mainpic/xuan.png");
    sp[2]->setPosition(Point(320,560));
    this->addChild(sp[2]);
    sp[3]=Sprite::create("mainpic/ze.png");
    sp[3]->setPosition(Point(440,560));
    this->addChild(sp[3]);
    
    sp[0]->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.2, -10),RotateBy::create(0.2, 10), NULL)));
    sp[1]->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.3, -10),RotateBy::create(0.2, 10), NULL)));
    sp[2]->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.2, -10),RotateBy::create(0.3, 10), NULL)));
    sp[3]->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.2, -10),RotateBy::create(0.2, 10), NULL)));
        
//    创建关卡1菜单项
    MenuItemImage* GKone = MenuItemImage::create(
                        "mainpic/GK1.png",			//正常图片
                        "mainpic/GK1p.png",			//被按下时图片
                        CC_CALLBACK_0(ChooseGKLayer::GKCallbackone, this) //点击时被回调的方法
                                     );
    //设置其位置
    GKone->setPosition(Point(100,400));
//    创建关卡2菜单项
    MenuItemImage* GKtwo = MenuItemImage::create(
                            "mainpic/GK2.png",			//正常图片
                            "mainpic/GK2p.png",			//按下时的图片
                            CC_CALLBACK_0(ChooseGKLayer::GKCallbacktwo, this) //点击时被回调的方法
                                                 );
    //设置其位置
    GKtwo->setPosition(Point(270,400));
//    创建关卡3菜单项
    MenuItemImage* GKthree = MenuItemImage::create(
                            "mainpic/GK3.png",			//正常图片
                            "mainpic/GK3p.png",		//按下时的图片
                            CC_CALLBACK_0(ChooseGKLayer::GKCallbackthree, this) //点击时被回调的方法
                                                );
    //设置其位置
    GKthree->setPosition(Point(440,400));
    MenuItemImage* back = MenuItemImage::create(
                                                "mainpic/back.png",	//正常图片
                                                "mainpic/backp.png",	//按下时图片
                                                CC_CALLBACK_0(ChooseGKLayer::backCallback, this) //点击时被回调的方法
                                                );
    //设置其位置
    back->setPosition(Point(480,50));
    //创建菜单对象
    Menu* menu = Menu::create(GKone,GKtwo,GKthree,back,NULL);
    //设置其位置
    menu->setPosition(Point::ZERO);
    //将其添加到布景中
    this->addChild(menu, 2);
    return true;
}
void ChooseGKLayer::GKCallbackone()//点击关卡1被回调的方法
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    设置关卡计数器为1
    ChooseGKLayer::gk=1;
//    切换到游戏场景界面
    sbsm->goGameScene();
}
void ChooseGKLayer::GKCallbacktwo()//点击关卡2被回调的方法
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    设置关卡计数器为2
    ChooseGKLayer::gk=2;
//  切换到游戏场景界面
    sbsm->goGameScene();
}
void ChooseGKLayer::GKCallbackthree()//点击关卡3被回调的方法
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    设置关卡计数器为3
    ChooseGKLayer::gk=3;
//    切换到游戏场景界面
    sbsm->goGameScene();

}
void ChooseGKLayer::backCallback()//点击返回菜单项被回调的方法
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    切换到主界面
    sbsm->goMainScene();
}
