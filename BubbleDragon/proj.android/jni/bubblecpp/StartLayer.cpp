#include "StartLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"

/**
 * @author zhenyu_lu
 * StartLayer 程序启动加载动画和菜单布景
 * {@code c++}
 * */

//引用cocos2d名称空间
using namespace cocos2d;

bool StartLayer::soundB=true;

//实现初始化布景方法
bool StartLayer::init()
{
	//调用父类的初始化方法
	if ( !Layer::init() )
	{
		return false;
	}
	 //获取可见区域的尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
//    创建一个精灵当作背景图片
	loadingPic = Sprite::create("pic/loading.jpg");
//    设置其位置
	loadingPic->setPosition(visibleSize.width/2,visibleSize.height/2);
//    将其添加到布景中
	this->addChild(loadingPic,0);
	logoPic = Sprite::create("mainpic/menu_title.png");
	logoPic->setPosition(visibleSize.width/2,3 * visibleSize.height/4);
	this->addChild(logoPic,0);
    
    lPros = Label::createWithTTF("0%","fonts/FZKATJW.ttf",50);
    lPros->setPosition(Point(270,480));
    this->addChild(lPros,1);
    
    initSound();
	loadingTexturesAsync();
	return true;
}
void StartLayer::loadingTexturesAsync()
{
//    将需要加载到图片储存在一个数组中
	std::string sa[16]=
	{
		"pic/ball_1.png","pic/ball_2.png","pic/ball_3.png","pic/ball_4.png",
		"pic/ball_5.png","pic/ball_6.png","pic/ball_7.png","pic/ball_8.png",
		"pic/frozen_1.png","pic/frozen_2.png","pic/frozen_3.png","pic/frozen_4.png",
		"pic/frozen_5.png","pic/frozen_6.png","pic/frozen_7.png","pic/frozen_8.png"
	};
	for(int i=0;i<16;i++)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(  	 //加载图片资源
						sa[i],		  									//图片资源路径
                        CC_CALLBACK_1(StartLayer::loadingCallBack, this) //加载完成时被回调的方法
			);
	}
}
void StartLayer::loadingCallBack(Texture2D* tt)//加载完成时被回调的方法
{
//    记录加载的图片资源的个数
	jd=jd+1;
	if(jd==16)
	{// 如果加载完成
        lPros->setString("100%");
        this->removeChild(lPros);
//		     获取可见区域尺寸
        	visibleSize = Director::getInstance()->getVisibleSize();
//		     获取可见区域原点坐标
        	origin = Director::getInstance()->getVisibleOrigin();
//        删除加载时用作背景的精灵对象
		this->removeChild(loadingPic);
//        创建一个精灵用于显示当前背景
		Sprite* mainbg = Sprite::create("mainpic/bg.png");
//        设置其位置
		mainbg->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
//        将其添加到布景中
		this->addChild(mainbg,0);
        
        Sprite* sppl = Sprite::create("mainpic/menu_title.png");
        sppl->setPosition(Point(270,800));
        this->addChild(sppl,2);
        
        ParticleSystemQuad* psq = ParticleSystemQuad::create("lzxt/stars.plist");
        psq->setBlendAdditive(true);
        this->addChild(psq, 10);
        psq->setPosition( Point( 270, 800) );
        
        ParticleSystemQuad* psq1 = ParticleSystemQuad::create("lzxt/point3.plist");
        psq1->setBlendAdditive(true);
        this->addChild(psq1, 10);
        psq1->setPosition( Point( 449, 83) );
        
        ParticleSystemQuad* psqp = ParticleSystemQuad::create("lzxt/point.plist");
        psqp->setBlendAdditive(true);
        this->addChild(psqp, 10);
        psqp->setPosition(Point( 100, 183));
        
        
        
//        创建一个开始菜单项
		MenuItemImage* puzzle = MenuItemImage::create
		(
			   "mainpic/start.png",	//正常图片
			   "mainpic/startp.png",	//按下时图片
			   CC_CALLBACK_0(StartLayer::startCallback, this) //点击被回调掉的方法
		);
		//设置其位置
		puzzle->setPosition(Point(270,630));
        
		//创建帮助菜单项
		MenuItemImage* arcade = MenuItemImage::create(
			   "mainpic/help.png",		//正常图片
			   "mainpic/helpp.png",     //按下时的图片
			   CC_CALLBACK_0(StartLayer::helpCallback, this) //点击时被回调的方法
		);

		//设置其位置
		arcade->setPosition(Point(270,530));
        //创建帮助菜单项
		MenuItemImage* jfb = MenuItemImage::create(
              "mainpic/board.png",	//正常图片
              "mainpic/boardp.png",	//按下时的图片
              CC_CALLBACK_0(StartLayer::phbCallback, this) //点击时被回调的方法
        );
		//设置其位置
		jfb->setPosition(Point(270,430));
		//创建关于菜单项
		MenuItemImage* aboutUS = MenuItemImage::create(
			   "mainpic/aboutus.png",	//正常图片
			   "mainpic/aboutusp.png",	//按下时的图片
			   CC_CALLBACK_0(StartLayer::aboutCallback, this) //按下时被回调的方法
		);
        
		//设置其位置
		aboutUS->setPosition(Point(270,230));
    
        Sprite* s = Sprite::create("mainpic/yinxiao.png");
        s->setPosition(Point(270,330));
        this->addChild(s);
        //   创建返回菜单项
        soundon = MenuItemImage::create(
          "mainpic/yinyue.png",	//正常图片
          "mainpic/jingyin.png",	//按下图片
                 CC_CALLBACK_0(StartLayer::soundCallback, this) //被点击时回调的方法
               );
        //设置其位置
        soundon->setPosition(Point(400,330));
        soundon->setScale(0.5);
        //   创建返回菜单项
        soundoff = MenuItemImage::create(
         "mainpic/jingyin.png",	//正常图片
         "mainpic/yinyue.png",	//按下图片
          CC_CALLBACK_0(StartLayer::soundCallback, this) //被点击时回调的方法
            );
        //设置其位置
        soundoff->setPosition(Point(400,330));
        soundoff->setScale(0.5);
        
		//创建一个菜单对象
		Menu* menu = Menu::create(puzzle,arcade,aboutUS,soundon,soundoff,jfb,NULL);
		//设置其位置
		menu->setPosition(Point::ZERO);
		//将其添加到布景中
		this->addChild(menu, 2);
        
        if(soundB)
        {
            soundon->setVisible(true);
            soundoff->setVisible(false);
            //开始播放背景音乐，true表示循环
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_scene_bg.mp3",true);
        }else{
            soundon->setVisible(false);
            soundoff->setVisible(true);
        }
	}else
    {
        lPros->setString(StringUtils::format("%d",100/16*jd)+"%");
    }

	//创建关闭菜单项
	    auto closeItem = MenuItemImage::create
	    (
			   "CloseNormal.png",	//平时的图片
			   "CloseSelected.png",	//选中时的图片
			   CC_CALLBACK_1(StartLayer::menuCloseCallback, this) //点击时执行的回调方法
		);

	    //设置关闭菜单项的位置
	   	closeItem->setPosition
	   	(
	   		Point
	   		(
	   			origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,//X坐标
	            origin.y + closeItem->getContentSize().height/2						//Y坐标
	        )
	    );

	   	//创建菜单对象
	   	auto closeMenu = Menu::create(closeItem, NULL);
	   	//设置菜单位置
	   	closeMenu->setPosition(Point::ZERO);
	   	//将菜单添加到布景中
	   	this->addChild(closeMenu, 1);
}

void StartLayer::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void StartLayer::initSound()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(
	                                                                   "sound/game_scene_bg.mp3"
	                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/shijian.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/winp.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/regame.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/stickp.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/hit.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/explodeEffect.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/caidanyin.mp3"
                                                                   );
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
                                                                   "sound/losep.mp3"
                                                                   );
}
//点击开始游戏被回调的方法
void StartLayer::startCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    切换到选关界面
    sbsm->goGKScene();
}
//播放／暂停声音菜单被点击的回调方法
void StartLayer::soundCallback()
{
    if(!StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    if (soundB==true)
    {//如果原本时播放声音，则此时将声音暂停
//        设置播放声音菜单不显示
        soundon->setVisible(false);
//        设置关闭声音菜单显示
        soundoff->setVisible(true);
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    else
    {//播放声音
//        设置播放声音菜单为可见
        soundon->setVisible(true);
//        设置暂停声音菜单为不可见
        soundoff->setVisible(false);
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
//    将声音的标志为设置为相反值
    soundB=!soundB;
}
//帮助菜单被点击时回调的方法
void StartLayer::helpCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    切换到帮助场景
    sbsm->gohelpScene();
}
//关于菜单被点击时回调的方法
void StartLayer::aboutCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
//    切换到关于菜单场景
    sbsm->goAboutUSScene();
}void StartLayer::phbCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
    }
    //    切换到关于记分板场景
    sbsm->goJbfScene();
}
