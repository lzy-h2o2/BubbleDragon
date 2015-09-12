#include "JFBLayer.h"
#include "ChooseGKLayer.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"

/**
 * @author zhenyu_lu
 * JFBLayer 排行布景
 * {@code c++}
 * */

bool JFBLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	Sprite *bg=Sprite::create("mainpic/bg1.png");
	bg->setPosition(Point(270,480));
    this->addChild(bg,0);
    
    Sprite *jfb=Sprite::create("mainpic/rank.png");
    jfb->setPosition(Point(290,540));
    this->addChild(jfb,1);
    getScore(currGK);
    MenuItemImage* prev = MenuItemImage::create(
                                                "mainpic/prev.png",
                                                "mainpic/prevp.png",
                                                CC_CALLBACK_0(JFBLayer::prevCallback, this)
                                                );
                                                prev->setPosition(Point(80,130));
    MenuItemImage* next = MenuItemImage::create(
                                                "mainpic/next.png",
                                                "mainpic/nextp.png",
                                                CC_CALLBACK_0(JFBLayer::nextCallback, this)
                                                );
                                                next->setPosition(Point(460,130));
    MenuItemImage* back = MenuItemImage::create(
                                                "mainpic/back.png",
                                                "mainpic/backp.png",
                                                CC_CALLBACK_0(JFBLayer::backCallback, this)
                                                );
    back->setPosition(Point(480,50));
    MenuItemImage* reset = MenuItemImage::create(
                                                "mainpic/reset.png",
                                                "mainpic/resetp.png",
                                                CC_CALLBACK_0(JFBLayer::resetScore, this)
                                                );
    reset->setPosition(Point(270,250));
   
    Menu* menu = Menu::create(back,prev,next,reset,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    return true;
}

void JFBLayer::getScore(int gk)
{
    Label* ll = Label::createWithTTF(StringUtils::format("%d",gk),"fonts/FZKATJW.ttf", 50);
    ll->setPosition(Point(265,730));
    ll->setColor(Color3B::RED);
    this->addChild(ll,2,22);
    for(int i=0;i<5;i++)
    {
        no[i]=Label::createWithTTF(StringUtils::format(
                                                       "%d",
                                                       UserDefault::getInstance()->getIntegerForKey(StringUtils::format("no%d",(gk-1)*5+i).c_str())),
                                   "fonts/FZKATJW.ttf", 50);
        no[i]->setPosition(Point(320,630));
        std::string st=
            StringUtils::format("%d",UserDefault::getInstance()->getIntegerForKey(StringUtils::format("no%d",i+(gk-1)*5).c_str()));
        for(int i=4;i>st.size();i--)
        {
            if(st.size()==3)
            {
                break;
            }
            st="0"+st;
        }
        no[i]->setString(st);
        this->addChild(no[i],2);
    }
    no[0]->setColor(Color3B::GREEN);
    no[1]->setColor(Color3B::YELLOW);
    no[2]->setColor(Color3B::GRAY);
    no[3]->setColor(Color3B::ORANGE);
    no[4]->setColor(Color3B::BLUE);
    
    no[4]->runAction(MoveTo::create(0.5,Point(320,360)));
    no[3]->runAction(MoveTo::create(0.5,Point(320,430)));
    no[2]->runAction(MoveTo::create(0.5,Point(320,500)));
    no[1]->runAction(MoveTo::create(0.5,Point(320,570)));
    no[0]->runAction(MoveTo::create(0.5,Point(320,640)));
}

void JFBLayer::backCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    sbsm->goMainScene();
}
void JFBLayer::prevCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    do{
        if(currGK==1)
        {
            currGK=3;
        }else
        {
            currGK--;
        }
        for(int i=0;i<5;i++)
        {
            this->removeChild(no[i]);
        }
        this->removeChildByTag(22);
        getScore(currGK);
    }while (0);
}
void JFBLayer::nextCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    do{
        if(currGK==3)
        {
            currGK=1;
        }else
        {
            currGK++;
        }
        for(int i=0;i<5;i++)
        {
            this->removeChild(no[i]);
        }
        this->removeChildByTag(22);
        getScore(currGK);
    }while (0);
}

void JFBLayer::resetScore()
{
    no[0]->setString("000");
    no[1]->setString("000");
    no[2]->setString("000");
    no[3]->setString("000");
    no[4]->setString("000");
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",(currGK-1)*5+0).c_str(),0);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",(currGK-1)*5+1).c_str(),0);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",(currGK-1)*5+2).c_str(),0);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",(currGK-1)*5+3).c_str(),0);
    UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",(currGK-1)*5+4).c_str(),0);
}

