#include "HelpLayer.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"

/**
 * @author zhenyu_lu
 * HelpLayer 帮助布景
 * {@code c++}
 * */

bool HelpLayer::init()
{
    //调用父类的初始化方法
	if ( !Layer::init() )
	{
		return false;
	}
//    创建一个用于显示背景的精灵
    bg=Sprite::create("mainpic/bg1.png");
//    设置其位置
    bg->setPosition(Point(270,480));
//    将其添加到布景中
    this->addChild(bg,0);

//    创建一个介绍游戏玩法到精灵
    helpOne =Sprite::create("mainpic/helpTP.png");
//    设置其位置
    helpOne->setPosition(Point(270,480));
//    将其添加到布景中
    this->addChild(helpOne,1,1);//（node，ZOrde，tag）
    
    //    创建一个介绍游戏玩法到精灵
    helpTwo=Sprite::create("mainpic/helpPPLP.png");
    //    设置其位置
    helpTwo->setPosition(Point(810,480));
    //    将其添加到布景中
    this->addChild(helpTwo,1,2);
    
    prev = MenuItemImage::create(
                                                "mainpic/prev.png",	//正常图片
                                                "mainpic/prevp.png",	//按下时的图片
                                                CC_CALLBACK_0(HelpLayer::prevCallback, this) //被点击时回调的方法
                                                );
    //设置其位置
    prev->setPosition(Point(80,130));
    //创建返回菜单项
    next = MenuItemImage::create(
                                                "mainpic/next.png",	//正常图片
                                                "mainpic/nextp.png",	//按下时的图片
                                                CC_CALLBACK_0(HelpLayer::nextCallback, this) //被点击时回调的方法
                                                );
    //设置其位置
    next->setPosition(Point(460,130));

    //创建返回菜单项
    MenuItemImage* back = MenuItemImage::create(
                        "mainpic/back.png",	//正常图片
                        "mainpic/backp.png",	//按下时的图片
                        CC_CALLBACK_0(HelpLayer::backCallback, this) //被点击时回调的方法
                                                );
    //设置其位置
    back->setPosition(Point(480,50));
    Menu* menu = Menu::create(back,prev,next,NULL);
    //设置其位置
    menu->setPosition(Point::ZERO);
    //将其添加到布景中
    this->addChild(menu, 2);
    return true;
}
//点击返回菜单时被回调的方法
void HelpLayer::backCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    切换到主界面
    sbsm->goMainScene();
}
void HelpLayer::nextCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    prev->setEnabled(false);
    next->setEnabled(false);
    if(ms==2)
    {
        bg->setPosition(Point(810,480));
        helpOne->setPosition(Point(810,480));
        ms=1;
    }else
    {
        helpTwo->setPosition(Point(810,480));
        ms=2;
    }
    bg->runAction(MoveBy::create(1, Point(-540,0)));
    helpOne->runAction(Sequence::create(MoveBy::create(1, Point(-540,0)),
                                        CallFunc::create(CC_CALLBACK_0(HelpLayer::setMenuEnable,this))
                                        ,NULL));
    helpTwo->runAction(MoveBy::create(1, Point(-540,0)));
}
void HelpLayer::prevCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    prev->setEnabled(false);
    next->setEnabled(false);
    if(ms==2)
    {
        bg->setPosition(Point(-270,480));
        helpOne->setPosition(Point(-270,480));
        ms=1;
    }else
    {
        helpTwo->setPosition(Point(-270,480));
        ms=2;
    }
    bg->runAction(MoveBy::create(1, Point(540,0)));
    helpOne->runAction(Sequence::create(
                                        MoveBy::create(1, Point(540,0)),
                                        CallFunc::create(CC_CALLBACK_0(HelpLayer::setMenuEnable,this))
                                        ,NULL));
    helpTwo->runAction(MoveBy::create(1, Point(540,0)));
}
void HelpLayer::setMenuEnable()
{
    prev->setEnabled(true);
    next->setEnabled(true);
}
