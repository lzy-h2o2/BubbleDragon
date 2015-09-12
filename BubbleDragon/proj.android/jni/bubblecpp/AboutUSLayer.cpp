#include "AboutUSLayer.h"
#include "StartLayer.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"

/**
 * @author zhenyu_lu
 * AboutUSLayer 关于布景
 * {@code c++}
 * */
bool AboutUSLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
    Sprite* bg = Sprite::create("mainpic/bg.png");
    bg->setPosition(Point(270,480));
    this->addChild(bg,0);
    
    Sprite* sppl = Sprite::create("mainpic/menu_title.png");
    sppl->setPosition(Point(270,800));
    this->addChild(sppl,2);
    ParticleSystemQuad* psq = ParticleSystemQuad::create("lzxt/stars.plist");//粒子系统
    psq->setBlendAdditive(true);
    this->addChild(psq, 10);
    psq->setPosition( Point( 270, 800) );    
    
    Label *yxLabel1 = Label::createWithTTF("\u5362\u632f\u96e8", "fonts/FZKATJW.ttf", 50);
    yxLabel1->setPosition(Point(270,540));
    yxLabel1->setColor(Color3B(247,232,211));
    yxLabel1->enableOutline(Color4B(124,66,24,255),4);
    this->addChild(yxLabel1,1);
    
    Label *yxLabel2 = Label::createWithTTF("\u7248\u6743\u6240\u6709", "fonts/FZKATJW.ttf", 50);
    yxLabel2->setPosition(Point(270,460));
    yxLabel2->setColor(Color3B(247,232,211));
    yxLabel2->enableOutline(Color4B(124,66,24,255),4);
    this->addChild(yxLabel2,1);

    Label *yxLabel3 = Label::createWithTTF("Copyright ®2015", "fonts/sea.ttf", 20);
        yxLabel3->setPosition(Point(270,380));
        yxLabel3->setColor(Color3B(247,232,211));
        yxLabel3->enableOutline(Color4B(124,66,24,255),4);
        this->addChild(yxLabel3,1);

    Label *yxLabel4 = Label::createWithTTF("H2O2 Software Studios", "fonts/sea.ttf", 20);
        yxLabel4->setPosition(Point(270,340));
        yxLabel4->setColor(Color3B(247,232,211));
        yxLabel4->enableOutline(Color4B(124,66,24,255),4);
        this->addChild(yxLabel4,1);


    MenuItemImage* back = MenuItemImage::create(
                                                "mainpic/back.png",
                                                "mainpic/backp.png",
                                                CC_CALLBACK_0(AboutUSLayer::backCallback, this)
  );

    back->setPosition(Point(480,50));
    Menu* menu = Menu::create(back,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    return true;
}

void AboutUSLayer::backCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    sbsm->goMainScene();
}
