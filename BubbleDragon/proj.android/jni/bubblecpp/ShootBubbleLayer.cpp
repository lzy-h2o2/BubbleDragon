#include "ShootBubbleLayer.h"
#include "cocos2d.h"
#include <math.h>
#include "AppMacros.h"
#include "vector"
#include "SimpleAudioEngine.h"
#include "extensions/cocos-ext.h"
#include "ShootBubbleSceneManager.h"
#include "ChooseGKLayer.h"
#include "StartLayer.h"

using namespace cocos2d;
USING_NS_CC_EXT;

/**
 * @author zhenyu_lu
 * ShootBubbleLayer 游戏射击主界面布景
 * {@code c++}
 * */

//初始化游戏布景
bool ShootBubbleLayer::init()
{
	//调用父类到初始化方法
    if ( !Layer::init())
    {
        return false;
    }
    for(int i=0;i<5;i++)
    {
        no[i]=Label::createWithTTF(StringUtils::format(
                                   "%d",
                                   UserDefault::getInstance()->getIntegerForKey(StringUtils::format("no%d",i).c_str())),
                                   "fonts/FZKATJW.ttf", 50);
        no[i]->setPosition(Point(300,570-i*40));
        this->addChild(no[i],DASHBOARD_LEVEL+1);
        no[i]->setVisible(false);
    }
    no[0]->setColor(Color3B(120,180,250));
    no[1]->setColor(Color3B::YELLOW);
    no[2]->setColor(Color3B::GRAY);
    no[3]->setColor(Color3B::ORANGE);
    no[4]->setColor(Color3B::RED);
    
    path = new std::vector<Point>();
	allBall = new std::vector<Sprite*>();
	RMball = new std::vector<Point>();
//    创建NodGird对象
    effectGrid = NodeGrid::create();
//    将NodeGird对象添加到布景中
    this->addChild(effectGrid, GAME_STOP_LEVEL+1);

	//获取可见区域尺寸
	visibleSize = Director::getInstance()->getVisibleSize();
	//获取可见区域原点坐标
	origin = Director::getInstance()->getVisibleOrigin();
//    创建一个文本标签，用于显示分数
	FSLabel = LabelAtlas::create("0","pic/fst.png",17,22,'0');
//    设置其位置
	FSLabel->setPosition(Point(visibleSize.width/2 + 50,930));
    FSLabel->setAnchorPoint(Point(0,0.5));
//    将其添加到布景中
	this->addChild(FSLabel,DASHBOARD_LEVEL+1);
	tipLabel = Label::createWithTTF("\u8ba1\u65f6\uff1a", "fonts/FZKATJW.ttf", 28);
	tipLabel->setPosition(visibleSize.width/2, 930);
	tipLabel->setColor(Color3B::YELLOW);
	tipLabel->enableOutline(Color4B(124,66,24,255),4);
	this->addChild(tipLabel,60);
	launcher = Sprite::create("pic/launcher.png");
	launcher->setAnchorPoint(Point(0.5,0.43));
	launcher->setPosition(visibleSize.width/2+2,140);
	this->addChild(launcher,50);
    //创建暂停按钮
    MenuItemImage* pauseMenu = MenuItemImage::create(
         "pic/gamepause.png",
         "pic/gamepause.png",
          CC_CALLBACK_0(ShootBubbleLayer::puaseCallback, this)
                                                     );
    pauseMenu->setPosition(Point(500,40));
    Menu* menu = Menu::create(pauseMenu,NULL);
    //设置其位置
    menu->setPosition(Point::ZERO);
    //将其添加到布景中
    this->addChild(menu, 2,4);
	//初始化球
	intiBall();
	//初始化所有可以落球的点
	initLocation();
	//初始化关卡数组
	initIsEmpty();
	//拷贝当前点地图，供操作
	copyIsEmpty();
	//画球
	drawBall();
    
	//初始化
	cbx=CBX_INIT;
	cby=CBY_INIT;
	
	cbpx=0;
	cbpy=0;
	
	vx=(float)(1*sin(PI/2-direction));
	vy=(float)(1*cos(PI/2-direction));
	minJLBall=MAX_VALUE;

	
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan = CC_CALLBACK_2(ShootBubbleLayer::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);


    Director* director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->schedule(SEL_SCHEDULE(&ShootBubbleLayer::updatetime), this, 1, false);
    
    return true;
}
void ShootBubbleLayer::updatetime()
{
    timeScore=timeScore+1;
    FSLabel->setString(StringUtils::format("%d",timeScore));
}

void ShootBubbleLayer::intiBall()
{
	//产生一个1-8的随机数
	srand((unsigned)time(NULL));
	int i = rand()%8+1;
	//创建一个精灵对象
	ballNextStart=Sprite::createWithTexture(
			Director::getInstance()->getTextureCache()
				->addImage("pic/ball_"+StringUtils::format("%d",i)+".png"));
	ballNextStart->setPosition(Point(visibleSize.width/2,50));
	this->addChild(ballNextStart,GAME_LEVEL);
	//产生一个1-8的随机数
	nextBallColor=i;
	int j = rand()%8+1;
	//创建一个精灵对象
	ballStart = Sprite::createWithTexture(
			Director::getInstance()->getTextureCache()
				->addImage("pic/ball_"+StringUtils::format("%d",j)+".png"));
    ballStart->setPosition(Point(visibleSize.width/2,140));
	this->addChild(ballStart,GAME_LEVEL);
//	将下一个将要发射的球的颜色记录为当前颜色
	currBallColor=j;
}
//初始化关卡的方法
void ShootBubbleLayer::initIsEmpty()
{
    switch (ChooseGKLayer::gk)
    {
        case 1:
        	bg = Sprite::create("mainpic/bg1.png");
        	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
        	this->addChild(bg, BACKGROUND_LEVEL);
        	compressor1 = Sprite::create("pic/compressor2.png");
        	compressor1->setPosition(visibleSize.width/2,visibleSize.height-compressor1->getContentSize().height/2);
        	this->addChild(compressor1,DJ_LEVEL,50);
        	for (int i = 0; i < ARRAYSIZE; i++) {
        		for (int j = 0; j < ARRAYCOL; j++) {
        			IsEmpty[i][j] = GKONE[i][j];
        			/*if (ChooseGKLayer::gk == 1) {
        				IsEmpty[i][j] = GKONE[i][j];
        			} else {
        				IsEmpty[i][j] = GKTWO[i][j];
        			}*/
        		}
        	}
        	break;
        case 2:
            bg = Sprite::create("mainpic/bg2.png");
            bg->setPosition(visibleSize.width/2,visibleSize.height/2);
            this->addChild(bg,BACKGROUND_LEVEL);
            compressor2 = Sprite::create("pic/compressor2.png");
            compressor2->setPosition(visibleSize.width/2,visibleSize.height-compressor2->getContentSize().height/2);
            this->addChild(compressor2,DJ_LEVEL,50);
            for(int i=0;i<ARRAYSIZE;i++)
            {
                for(int j=0;j<ARRAYCOL;j++)
                {
                	IsEmpty[i][j]=GKTWO[i][j];
                    /*if(ChooseGKLayer::gk==1)
                    {
                        IsEmpty[i][j]=GKONE[i][j];
                    }else
                    {
                      IsEmpty[i][j]=GKTWO[i][j];
                    }*/
                }
            }
            break;
        case 3:
            bg = Sprite::create("pic/background.jpg");
            bg->setPosition(visibleSize.width/2,visibleSize.height/2);
            this->addChild(bg,BACKGROUND_LEVEL);
            compressor = Sprite::create("pic/compressor.png");
            compressor->setPosition(visibleSize.width/2,visibleSize.height-compressor->getContentSize().height/2);
            this->addChild(compressor,DJ_LEVEL,50);
            compressor_bodyL = Scale9Sprite::create("pic/compressor_body.png",Rect(0,0,50,0.1),Rect(0,0,50,0.1));
            compressor_bodyL->setAnchorPoint(Point(0.5,0));
            compressor_bodyL->setPosition(Point(93,visibleSize.height));
            this->addChild(compressor_bodyL,DJ_LEVEL,51);
            compressor_bodyR = Scale9Sprite::create("pic/compressor_body.png",Rect(0,0,50,0.1),Rect(0,0,50,0.1));
            compressor_bodyR->setAnchorPoint(Point(0.5,0));
            compressor_bodyR->setPosition(Point(445,visibleSize.height));
            this->addChild(compressor_bodyR,DJ_LEVEL,52);
            Director* director = Director::getInstance();
            auto sched = director->getScheduler();
            sched->schedule(SEL_SCHEDULE(&ShootBubbleLayer::update), this, 15, false);
            for(int i=0;i<ARRAYSIZE;i++)
            {
                for(int j=0;j<ARRAYCOL;j++)
                {
                    IsEmpty[i][j]=GKTHREE[i][j];
                }
            }
            break;
    }

}
//拷贝当前地图数组
void ShootBubbleLayer::copyIsEmpty()
{
	for(int i=0;i<ARRAYSIZE;i++)
	{
		for(int j=0;j<ARRAYCOL;j++)
		{
			IsEmptyTemp[i][j]=IsEmpty[i][j];
		}
	}
}
//拷贝经过操作后的地图数组
void ShootBubbleLayer::copyIsEmptyTemp()
{
	for(int i=0;i<ARRAYSIZE;i++)
	{
		for(int j=0;j<ARRAYCOL;j++)
		{
			IsEmpty[i][j]=IsEmptyTemp[i][j];
		}
	}
}
//画球
void ShootBubbleLayer::drawBall()
{
	Sprite* tempSprite=NULL;
	std::string s;
	if(IsGameOver)
	{
		s="frozen";
	}else{
		s="ball";
	}
	for(int i=0;i<ARRAYSIZE;i++)
	{
		for(int j=0;j<ARRAYCOL;j++)
		{
			if(IsEmpty[i][j]==0)
			{
				continue;
			}
			switch(IsEmpty[i][j])
			{
			case 1:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_1.png"));
			break;
			case 2:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_2.png"));
			break;
			case 3:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_3.png"));
			break;
			case 4:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_4.png"));
			break;
			case 5:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_5.png"));
			break;
			case 6:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_6.png"));
			break;
			case 7:
					tempSprite=Sprite::createWithTexture(
						Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_7.png"));
			break;
			case 8:
						tempSprite=Sprite::createWithTexture(
							Director::getInstance()->getTextureCache()
							->addImage("pic/"+s+"_8.png"));
			break;
			}
			tempSprite->setPosition(bLocation[i][j].x,bLocation[i][j].y);
            this->addChild(tempSprite, GAME_LEVEL);
			allBall->push_back(tempSprite);
		}
	}
}
//初始化所有可以落球的点
void ShootBubbleLayer::initLocation()
{
	int a=0;//数组行号
	int b=0;//数组列数
	for(int i=850;i>140;i-=R3S)
	{
		if(a%2==0)						//判断当前计算泡泡的行号是否为偶数
		{
			for(int j=30;j<540;j+=60)
			{
				bLocation[a][b].x=j;	//记录横坐标
				bLocation[a][b].y=i;	//记录纵坐标
				b++;					//列数加1，用于计算下一列
			}
			b=0;						//计算完一行后将列号重置
		}
		if(a%2==1)
		{
			for(int j=60;j<540;j+=60)
			{
				bLocation[a][b].x=j;
				bLocation[a][b].y=i;
				b++;
			}
			b=0;
		}
		a++;
	}
}
//添加被射击的球
void ShootBubbleLayer::addBall()
{
	srand((unsigned)time(NULL));
	int j = rand()%8+1;
	ballNextStart = Sprite::createWithTexture(
			Director::getInstance()->getTextureCache()
			->addImage("pic/ball_"+StringUtils::format("%d",j)+".png"));
	ballNextStart->setPosition(Point(visibleSize.width/2,50));
    //===================
	this->addChild(ballNextStart,GAME_LEVEL);
	currBallColor=nextBallColor;
	nextBallColor=j;
}
//触摸开始
bool ShootBubbleLayer::onTouchBegan(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	auto location = target->convertToNodeSpace(touch->getLocation());
	shootBall(location);
	return false;
}
//发射球的方法
void ShootBubbleLayer::shootBall(Point location)
{
	do{
        if(moveFlag)
		{//如果球正在运动，则不发射
			break;
		}
		if(IsGameOver)
		{//若已经结束游戏，则重信开始
            if(StartLayer::soundB)
            {
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/regame.mp3");
            }
            gameRestartFUNC();
           	break;
		}
        if(StartLayer::soundB)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/hit.mp3");
        }
		//将当前球的颜色设置为正在发射球的颜色
		shootBallColor=currBallColor;
		//设置球正在运动的标志位位true
		moveFlag=true;
		//获取触摸点位置
		float touchX = location.x;
		float touchY = location.y;
		if(touchY<145){moveFlag=false;break;}
		//获取当前球点位置
		Point ballPosition = ballStart->getPosition();
		float ballSX = ballPosition.x;
		float ballSY = ballPosition.y;
		//计算x,y方向的增量
		float dx=touchX-ballSX;
		float dy=touchY-ballSY;
		//求出发射角度的弧度值
		direction=(float)atan2(dy,dx);
		//判断是否有枪膛，以便设置其方向
        if(launcher!=NULL)
        {
            launcher->setRotation(90-direction/PI*180);
        }
		//x,y方向的单位向量
		vx=(float)(1*sin(PI/2-direction));
		vy=(float)(1*cos(PI/2-direction));
		//计算球运行路径
		calPath();
		//计数器，记录当前的路线条数
		int countTemp=0;

		FiniteTimeAction* preAc;
		//获取球发射点点位置坐标
		Point lastPoint=Point(270,140);
		Point currPoint=Point(270,140);
		std::vector<Point>::iterator tempPoint;
		for(tempPoint = path->begin();tempPoint != path->end();tempPoint++)
		{
			currPoint=*tempPoint;
			float dx=currPoint.x-lastPoint.x;
			float dy=currPoint.y-lastPoint.y;
			float dis =(float)sqrt(dx*dx+dy*dy);
			float moveT=0;
			moveT = dis/SPEED/3;
			if(countTemp==1)
			{
				MoveTo* mtemp=MoveTo::create(moveT,*tempPoint);
				preAc=mtemp;
			}
			else if(countTemp>1)
			{
				MoveTo* mtemp=MoveTo::create(moveT,*tempPoint);
				preAc=Sequence::createWithTwoActions(preAc,mtemp);
			}
			countTemp++;
			lastPoint=currPoint;
		}
		//将发射的球添加到向量中
		allBall->push_back(ballStart);
		//让发射的球沿路线运动
		ballStart->runAction(Sequence::createWithTwoActions(
							preAc,
							CallFunc::create(CC_CALLBACK_0(ShootBubbleLayer::moveFlagCallback,this))
																));
		ballNextStart->runAction(MoveTo::create(0.1,Point(270,140)));
		//将下一个球到指针赋值即将发射
		ballStart=ballNextStart;
		//添加一个球
		addBall();
	}while(0);
}
void ShootBubbleLayer::moveFlagCallback()
{
	do{//	搜索附近是否有相同颜色到球
			search(Row,Col);
			for(int i=0;i<ARRAYSIZE;i++)//遍历搜索路径的数组
			{
				for(int j=0;j<ARRAYCOL;j++)
				{
					Goneball[i][j]=0;
				}
			}
			//若只有一个
			if(RMCountballs==1)
			{
				IsEmpty[Row][Col]=shootBallColor;
			}
			//若有两个
			if(RMCountballs==2)
			{
				IsEmpty[Row][Col]=shootBallColor;
				copyIsEmpty();
			}
			//三个以上消除
			if(RMCountballs>=3)
			{
                RMballDY3();
			}
			std::vector<Sprite*>::iterator tempBall;
			for(tempBall = allBall->begin();tempBall!= allBall->end();tempBall++)
			{
				this->removeChild(*tempBall,true);
			}
			allBall->clear();
			//
			int countBall=0;
			for(int i=0;i<ARRAYSIZE;i++)
			{
				for(int j=0;j<ARRAYCOL;j++)
				{
					if(IsEmpty[i][j]!=0)
					{
						countBall++;
					}
				}
			}
			//无泡泡
			if(countBall==0)
			{
                if(StartLayer::soundB)
                {
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pic/winp.mp3");
                }               
                Sprite* gxgg=Sprite::create("pic/win_panel.png");
                gxgg->setPosition(Point(420,1000));
                this->addChild(gxgg,DASHBOARD_LEVEL+1,101);
                gxgg->runAction(
                                Sequence::create(
                                                 Spawn::create(
                                                               MoveTo::create(0.1, Point(420,800)),
                                                               ScaleTo::create(0.1, 0.8), NULL),
                                                 MoveBy::create(0.1, Point(10,10)),
                                                 MoveBy::create(0.1, Point(10,10))->reverse(),
                                                 MoveBy::create(0.1, Point(10,10)),
                                                 MoveBy::create(0.1, Point(10,10))->reverse(),
                                                 MoveBy::create(0.1, Point(10,10)),
                                                 MoveBy::create(0.1, Point(10,10))->reverse(),
                                                 NULL));
                phbMenu();
                FSLabel->runAction(Sequence::create(MoveTo::create(1,Point(340,700)),ScaleTo::create(1,5),ScaleTo::create(1,2), NULL));
				IsGameOver=true;
                effectGrid = NodeGrid::create();
                this->addChild(effectGrid);
				ParticleSystemQuad*  psq = ParticleExplosion::create();
				this->addChild(psq, 10);
				psq->setTexture( Director::getInstance()->
						getTextureCache()->addImage("lzxt/fire.png"));
				psq->setPosition(270,540);
				RMCountballs=1;
                Director* director = Director::getInstance();
                auto sched = director->getScheduler();
                sched->pauseTarget(this);
				break;
			}
            for (int i=0; i<ARRAYSIZE; i++)
            {
                for (int j=0; j<ARRAYCOL; j++)
                {
                    if (IsEmptyTemp[i][j]!=0)
                    {
                        maxRow=i;
                        break;
                    }
                }
            }
            gameStopCallback();
			drawBall();
			if(RMCountballs<3)
			{
				ParticleSystemQuad*  psq = ParticleExplosion::create();
				this->addChild(psq, 10);
				psq->setTexture( Director::getInstance()->
						getTextureCache()->addImage("lzxt/fire.png"));
				psq->setPosition(bLocation[Row][Col]);
				psq->setLife(1);
				psq->setScale(0.5);
				psq->setEmissionRate(psq->getTotalParticles()/psq->getLife());
                if(StartLayer::soundB)
                {
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pic/stickp.mp3");
                }
			}
			RMCountballs=1;
	}while(0);
	moveFlag=false;
}
void ShootBubbleLayer::RMballDY3()
{
    IsEmptyTemp[Row][Col]=0;
    for(int i=0;i<ARRAYSIZE;i++)
    {
        for(int j=0;j<ARRAYCOL;j++)
        {
            for(int i=0;i<ARRAYSIZE;i++)
            {
                for(int j=0;j<ARRAYCOL;j++)
                {
                    Goneball[i][j]=0;
                }
            }
            bool b=searchRoad(i,j);
            if(b)
            {
                continue;
            }else
            {
                IsEmptyTemp[i][j]=0;
            }
        }
    }
    //遍历所有球
    for(int i=0;i<ARRAYSIZE;i++)
    {
        for(int j=0;j<ARRAYCOL;j++)
        {
            //                        找出需要删除到球
            if(IsEmptyTemp[i][j]!=IsEmpty[i][j])
            {
                //将其添加到删除球的向量中
                RMball->push_back(Point(i,j));
                RMCountballs++;
            }
        }
    }
    RMball->push_back(Point(Row,Col));
    IsEmpty[Row][Col]=shootBallColor;
    ballFalled();
    copyIsEmptyTemp();
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pic/explodeEffect.mp3");
    }
    if(RMCountballs<8&&RMCountballs>=3)
    {
        pSprite = Sprite::create(StringUtils::format("pic/link%d.png",RMCountballs-4));
        pSprite->setPosition(Point(bLocation[Row][Col]));
        this->addChild(pSprite,DASHBOARD_LEVEL);
        pSprite->runAction(
                           Sequence::create(
                                            ScaleTo::create(1,2),
                                            FadeOut::create(2),
                                            NULL)
                           );
        
    }else if(RMCountballs>=8){
        pSprite = Sprite::create("pic/link6.png");
        pSprite->setPosition(Point(bLocation[Row][Col]));
        this->addChild(pSprite,DASHBOARD_LEVEL);
        pSprite->runAction(
                           Sequence::create(
                                            ScaleTo::create(1,2),
                                            FadeOut::create(2),
                                            NULL)
                           );
    }
}
void ShootBubbleLayer::ballFalled()
{
	float RMballX=0;
	int RMBallCount=0;
	std::vector<Point>::iterator RMBallTemp;
	for(RMBallTemp = RMball->begin();RMBallTemp!= RMball->end();RMBallTemp++)
	{
		RMballX=RMballX+bLocation[(int)RMBallTemp->x][(int)RMBallTemp->y].x;
		RMBallCount++;
	}
	float avgRMballX=RMballX/(float)RMBallCount;
	for(RMBallTemp = RMball->begin();RMBallTemp!= RMball->end();RMBallTemp++)
	{
		if(bLocation[(int)RMBallTemp->x][(int)RMBallTemp->y].x<avgRMballX)
		{
			ballFalling((int)RMBallTemp->x,(int)RMBallTemp->y,1);
		}else
		{
			ballFalling((int)RMBallTemp->x,(int)RMBallTemp->y,2);
		}
	}
	RMball->clear();
}
void ShootBubbleLayer::ballFalling(int row,int col,int LR)
{

	float tempCurrX=bLocation[row][col].x;
	float tempCurrY=bLocation[row][col].y;
	float dx=0;
	float dy=0;
	float h=0;
	int g=10;
	ccBezierConfig bezier1;
	int i = rand()%8+1;
	if(LR==1)
	{
		dx=tempCurrX-20*i;
	}else if(LR==2){
		dx=tempCurrX+20*i;
	}
	dy=tempCurrY+20*i;
	bezier1.controlPoint_1 = Point(dx,dy);
	h= 0.5*g*3*3;
	dy=tempCurrY+50-h;
	if(LR==1)
	{
		dx=tempCurrX-20*3;
	}else if(LR==2)
	{
		dx=tempCurrX+20*3;
	}
	bezier1.controlPoint_2 = Point(dx,dy);
	h= 0.5*g*15*15;
	dy=tempCurrY-h;
	if(LR==1)
	{
		dx=tempCurrX-20*15;
	}else if(LR==2)
	{
		dx=tempCurrX+20*15;
	}
	bezier1.endPosition = Point(dx,dy);
	Sprite* ballFall =Sprite::createWithTexture(
							Director::getInstance()->getTextureCache()
								->addImage("pic/ball_"+StringUtils::format("%d",IsEmpty[row][col])+".png"));
	ballFall->setPosition(Point(tempCurrX,tempCurrY));
	this->addChild(ballFall,GAME_LEVEL+1,RMTAG);
	ballFall->runAction(BezierTo::create(1,bezier1));
}
bool ShootBubbleLayer::searchRoad(int row,int col)
{
    Goneball[row][col]=1;
	if(fabs(bLocation[row][col].y-MAXHeight)<=1)
	{
		return true;
	}else if(row%2==1)
	{
		if(IsEmptyTemp[row-1][col]!=0&&row-1>=0&&Goneball[row-1][col]==0&&searchRoad(row-1,col))
		{
			return true;
		}else if(IsEmptyTemp[row-1][col+1]!=0&&row-1>=0&&col+1<ARRAYCOL&&Goneball[row-1][col+1]==0&&searchRoad(row-1,col+1))
		{
			return true;
		}else if(IsEmptyTemp[row][col-1]!=0&&col-1>=0&&Goneball[row][col-1]==0&&searchRoad(row,col-1))
        {
            return  true;
        }else if(IsEmptyTemp[row][col+1]!=0&&col+1<ARRAYCOL&&Goneball[row][col+1]==0&&searchRoad(row,col+1))
        {
            return true;
        }else if(IsEmptyTemp[row+1][col]!=0&&row+1<14&&Goneball[row+1][col]==0&&searchRoad(row+1,col))
        {
            return true;
        }else if(IsEmptyTemp[row+1][col+1]!=0&&row+1<14&&col+1<9&&Goneball[row+1][col+1]==0&&searchRoad(row+1,col+1))
        {
            return true;
        }
    }else if(row%2==0)
    {
		if(IsEmptyTemp[row-1][col-1]!=0&&row-1>=0&&col-1>=0&&Goneball[row-1][col-1]==0&&searchRoad(row-1,col-1))
		{
			return true;
		}else if(IsEmptyTemp[row-1][col]!=0&&row-1>=0&&Goneball[row-1][col]==0&&searchRoad(row-1,col))
		{
			return true;
		}else if(IsEmptyTemp[row][col-1]!=0&&col-1>=0&&Goneball[row][col-1]==0&&searchRoad(row,col-1))
        {
            return  true;
        }else if(IsEmptyTemp[row][col+1]!=0&&col+1<ARRAYCOL&&Goneball[row][col+1]==0&&searchRoad(row,col+1))
        {
            return true;
        }else if(IsEmptyTemp[row+1][col]!=0&&row+1<14&&Goneball[row+1][col]==0&&searchRoad(row+1,col))
        {
            return true;
        }else if(IsEmptyTemp[row+1][col-1]!=0&&row+1<14&&col-1>=0&&Goneball[row+1][col-1]==0&&searchRoad(row+1, col-1))
        {
            return true;
        }
    }
	return false;
}
float ShootBubbleLayer::callDisR()
{
    float X=510;
    float t=(X-cbx)/vx;
    xRight=X;
    yRight=cby+vy*t;
    float dx=xRight-cbx;
    float dy=yRight-cby;
    return (float)sqrt(dx*dx+dy*dy);
}
float ShootBubbleLayer::callDisU()
{
    float Y=MAXHeight;
    float t=(Y-cby)/vy;
    xUp=cbx+vx*t;
    yUp=Y;
    float dx=xUp-cbx;
    float dy=yUp-cby;
    return  (float)sqrt(dx*dx+dy*dy);
}
float ShootBubbleLayer::callDisL()
{
    float X=30;
    float t=(X-cbx)/vx;
    xLeft=X;
    yLeft=cby+vy*t;
    float dx=xLeft-cbx;
    float dy=yLeft-cby;
    return (float)sqrt(dx*dx+dy*dy);
}
void ShootBubbleLayer::calPath()
{
	path->clear();//清除向量中所有数据
	path->push_back(Point(cbx,cby));//将泡泡发射的起始点存储在数组中
	bool notFinish=true;
	while(notFinish)//泡泡未到达最终点
	{
		bool ballFlag=calEndBall();//判断能否碰到地图里面的泡泡
		if(notFinish)
		{
			if(vx>0)
			{
                float disRight=callDisR();//计算泡泡发射点与右壁的距离
                float disUp=callDisU();//计算泡泡发射点与上壁的距离
				if(ballFlag&&minJLBall<disUp&&minJLBall<disRight)//泡泡碰撞点比壁的碰撞点近，则结束
				{
					break;
				}
				if(disUp<disRight)//若先碰上壁则结束
				{
					if(ballFlag)//若前面计算成功过泡泡的碰撞
					{
						path->pop_back();//则删除泡泡碰撞路线
					}
					path->push_back(Point(xUp,yUp));
					cbpx=xUp;
					cbpy=yUp;
					notFinish=false;
				}
				else		//不先碰到壁
				{
					if(ballFlag)
					{
						path->pop_back();
					}
					path->push_back(Point(xRight,yRight));
					cbx=xRight;
					cby=yRight;
					vx=-vx;
					notFinish=true;
				}
			}else if(vx<0)
			{
                float disLeft=callDisL();//计算泡泡发射点与左壁的距离
                float disUp=callDisU();//计算泡泡发射点与上壁的距离
				if(ballFlag&&minJLBall<disUp&&minJLBall<disLeft)
				{
					break;
				}
				if(disUp<disLeft)
				{
					if(ballFlag)
					{
						path->pop_back();
					}
					path->push_back(Point(xUp,yUp));
					cbpx=xUp;
					cbpy=yUp;
					notFinish=false;
				}else
				{
					if(ballFlag)
					{
						path->pop_back();
					}
					path->push_back(Point(xLeft,yLeft));
					cbx=xLeft;
					cby=yLeft;
					vx=-vx;
					notFinish=true;
				}
			}
			else
			{
				if(ballFlag)//泡泡垂直发射
				{
					break;
				}
				float Y=MAXHeight;
				path->push_back(Point(cbx,Y));
				cbpx=cbx;
				cbpy=Y;
				notFinish=false;
			}
		}
	}
	int rowTemp=(int)((MAXHeight-cbpy)/R3S);//计算泡泡的行号
	int colTemp=0;//计算泡泡的列号
	if(rowTemp%2==0)
	{
		colTemp=(int)(cbpx/DR);
	}
	else
	{
		colTemp=(int)((cbpx-R)/DR);
	}
	Point wgLocation=calCenter(rowTemp,colTemp);
	cbpx=wgLocation.x;
	cbpy=wgLocation.y;
	path->push_back(Point(cbpx,cbpy));
	cbx=CBX_INIT;
	cby=CBY_INIT;
	IsEmptyTemp[rowTemp][colTemp]=shootBallColor;
	Row=rowTemp;
	Col=colTemp;
}
bool ShootBubbleLayer::calEndBall()
{
	int trow=-1;
	int tcol=-1;
	minJLBall=MAX_VALUE;
	float A=vy;
	float B=-vx;
	float C=vx*cby-vy*cbx;
	for(int i=0;i<ARRAYSIZE;i++)
	{
		for(int j=0;j<ARRAYCOL;j++)
		{
			if(IsEmptyTemp[i][j]==0)continue;
			Point centerTemp=calCenter(i,j);
			float dis= distance(A,B,C,centerTemp.x,centerTemp.y);
			if(dis>=DR)
			{
				continue;
			}
            float dx=centerTemp.x-cbx;
			float dy=centerTemp.y-cby;
			float L=(float)sqrt(dx*dx+dy*dy);
			float cdis=(float)sqrt(L*L-dis*dis);
			float K=(float)sqrt(DR*DR-dis*dis);
			float jl=cdis-K;
			if(jl<minJLBall)
			{
				trow=i;
				tcol=j;
				minJLBall=jl;
			}
		}
	}
	if(trow!=-1&&tcol!=-1)
    {
		cbpx=cbx+vx*minJLBall;
		cbpy=cby+vy*minJLBall;
		path->push_back(Point(cbpx,cbpy));
		return true;
	}
	else
	{
		return false;
	}
}
Point ShootBubbleLayer::calCenter(int row,int col)
{
	return bLocation[row][col];
}
float ShootBubbleLayer::distance(float A,float B,float C,float x,float y)
{
	float dis=(float)((A*x+B*y+C)/sqrt(A*A+B*B));
	return fabs(dis);
}
void ShootBubbleLayer::search(int row,int col)
{
    Goneball[row][col]=1;
	if(row%2==0)
	{
		if(Goneball[row-1][col-1]==0&&IsEmptyTemp[row-1][col-1]==shootBallColor&&row-1>=0&&col-1>=0)
		{
			IsEmptyTemp[row-1][col-1]=0;
			RMCountballs++;
			search(row-1,col-1);
		}
		if(Goneball[row+1][col-1]==0&&IsEmptyTemp[row+1][col-1]==shootBallColor&&row+1<ARRAYSIZE&&col-1>=0)
		{
			IsEmptyTemp[row+1][col-1]=0;
			RMCountballs++;
			search(row+1,col-1);
		}
	}else if(row%2!=0)
	{
		if(Goneball[row+1][col+1]==0&&IsEmptyTemp[row+1][col+1]==shootBallColor&&row+1<ARRAYSIZE&&col+1<ARRAYCOL)
		{
			IsEmptyTemp[row+1][col+1]=0;
			RMCountballs++;
			search(row+1,col+1);
		}
		if(Goneball[row-1][col+1]==0&&IsEmptyTemp[row-1][col+1]==shootBallColor&&row-1>=0&&col+1<ARRAYCOL)
		{
			IsEmptyTemp[row-1][col+1]=0;
			RMCountballs++;
			search(row-1,col+1);
		}
	}
	if(Goneball[row-1][col]==0&&IsEmptyTemp[row-1][col]==shootBallColor&&row-1>=0)
	{
		IsEmptyTemp[row-1][col]=0;
		RMCountballs++;
		search(row-1,col);
	}
	if(Goneball[row][col-1]==0&&IsEmptyTemp[row][col-1]==shootBallColor&&col-1>=0)
	{
        IsEmptyTemp[row][col-1]=0;
		RMCountballs++;
		search(row,col-1);
    }
	if(Goneball[row][col+1]==0&&IsEmptyTemp[row][col+1]==shootBallColor&&col+1<ARRAYCOL)
	{
		IsEmptyTemp[row][col+1]=0;
		RMCountballs++;
		search(row,col+1);
	}
	if(Goneball[row+1][col]==0&&IsEmptyTemp[row+1][col]==shootBallColor&&row+1<ARRAYSIZE)
	{
		IsEmptyTemp[row+1][col]=0;
		RMCountballs++;
		search(row+1,col);
	}
}

void ShootBubbleLayer::update()
{
	do{
		if(moveFlag==true)
		{
			break;
		}
        if(StartLayer::soundB)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/shijian.mp3");
        }        
		moveFlag=true;
		compressor->setPosition(Point(compressor->getPosition().x,compressor->getPosition().y-R3S));
		compressor_bodyL->setContentSize(Size(50, compressor_bodyL->getContentSize().height-R3S));
		compressor_bodyR->setContentSize(Size(50, compressor_bodyR->getContentSize().height-R3S));
		std::vector<Sprite*>::iterator tempBall;
		for(tempBall = allBall->begin();tempBall!= allBall->end();tempBall++)
		{
			this->removeChild(*tempBall,true);
		}
		updateLocation();
        for (int i=0; i<ARRAYSIZE; i++)
        {
            for (int j=0; j<ARRAYCOL; j++)
            {
                if (IsEmptyTemp[i][j]!=0) {
                    maxRow=i;
                }
            }
        }
        allBall->clear();
        gameStopCallback();
        drawBall();
		moveFlag=false;
	}while(0);

}
void ShootBubbleLayer::updateLocation()
{
	for(int i=0;i<ARRAYSIZE;i++)
	{
		for(int j=0;j<ARRAYCOL;j++)
		{
			bLocation[i][j].x=bLocation[i][j].x;
			bLocation[i][j].y=bLocation[i][j].y-R3S;
		}
	}
	MAXHeight=MAXHeight-R3S;
}
bool ShootBubbleLayer::gameStopCallback()
{
    if(bLocation[maxRow][1].y-140-R3S<=1)
        if(StartLayer::soundB)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/losep.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        Sprite* GOverS=Sprite::create("pic/lose.png");
        GOverS->setPosition(Point(270,540));
        this->addChild(GOverS,GAME_STOP_LEVEL,GOTAG);
        
        Label* stopLabel=Label::createWithTTF("点击重玩","fonts/FZKATJW.ttf",60);
        stopLabel->setPosition(Point(270,300));
        stopLabel->setColor(Color3B(247,232,211));
        stopLabel->enableOutline(Color4B(124,66,24,255),4);
        this->addChild(stopLabel,GAME_STOP_LEVEL+2,77);
        

        IsGameOver=true;
        effectGrid = NodeGrid::create();
        this->addChild(effectGrid, GAME_STOP_LEVEL+1);
        Director* director = Director::getInstance();
        auto sched = director->getScheduler();
        sched->pauseTarget(this);
        moveFlag=false;
        maxRow=0;
        for(int i=0;i<14;i++)
        {
            for(int j=0;j<9;j++)
            {
                if (IsEmptyTemp[i][j]==0){
                    continue;
                }
                Sprite* sp=Sprite::createWithTexture(Director::getInstance()->getTextureCache()
                                                     ->addImage(StringUtils::format("pic/ball_%d.png",IsEmptyTemp[i][j])));
                sp->cocos2d::Node::setPosition(bLocation[i][j]);
                effectGrid->addChild(sp,GAME_STOP_LEVEL+1);
                IsEmptyTemp[i][j]=0;
            }
        }
        Director::getInstance()->setDepthTest(false);
        effectGrid->runAction(ShuffleTiles::create(0.5f, Size(100,100), 25));
        return true;
    }
    return false;
}
void ShootBubbleLayer::puaseCallback()
{
    if(!isPause)
    {
        if(StartLayer::soundB)
        {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
            CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        }
        moveFlag=true;
        Director::getInstance()->pause();
        this->getChildByTag(4)->setVisible(false);
        
        //    创建一个背景
        Sprite* menuSprite= Sprite::create("pic/menu.png");
        //    设置其位置
        menuSprite->setPosition(Point(270,480));
        //    将其添加到布景中
        this->addChild(menuSprite,GAME_STOP_LEVEL,9);
        
        MenuItemImage* jxyx = MenuItemImage::create(
                                                   "pic/jixup.png",		//正常图片
                                                   "pic/jixu.png",	//按下时的图片
                                                   CC_CALLBACK_0(ShootBubbleLayer::puaseCallback, this) //点击时被回调的方法
                                                   );
		//设置其位置
		jxyx->setPosition(Point(270,570));
        jxyx->setScale(0.8);
        MenuItemImage* zcd = MenuItemImage::create(
                                                   "pic/zhucaidanp.png",		//正常图片
                                                   "pic/zhucaidan.png",	//按下时的图片
                                                   CC_CALLBACK_0(ShootBubbleLayer::menuStopCallback, this) //点击时被回调的方法
                                                   );
		//设置其位置
		zcd->setPosition(Point(270,480));
        zcd->setScale(0.8);
        MenuItemImage* cwbg = MenuItemImage::create(
                                                   "pic/cw.png",		//正常图片
                                                   "pic/cwp.png",	//按下时的图片
                                                   CC_CALLBACK_0(ShootBubbleLayer::menuStartCallback, this) //点击时被回调的方法
                                                   );
		//设置其位置
		cwbg->setPosition(Point(270,400));
        cwbg->setScale(0.8);
        
        
        Menu* menu = Menu::create(jxyx,zcd,cwbg,NULL);

		menu->setPosition(Point::ZERO);

		this->addChild(menu, GAME_STOP_LEVEL+3,3);
    }else
    {
        moveFlag=false;
        this->removeChildByTag(3);
        this->removeChildByTag(9);
        this->getChildByTag(4)->setVisible(true);
        Director::getInstance()->resume();
        if(StartLayer::soundB)
        {
        	CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
    }
    isPause=!isPause;
}
void ShootBubbleLayer::menuStopCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    Director::getInstance()->resume();
    isPause=!isPause;
    Director::getInstance()->resume();
    sbsm->goMainScene();
}
void ShootBubbleLayer::menuStartCallback()
{
    if(StartLayer::soundB)
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/caidanyin.mp3");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    isPause=!isPause;
    Director::getInstance()->resume();
    moveFlag=false;
    this->removeChildByTag(3);
    this->removeChildByTag(9);
    effectGrid = NodeGrid::create();
    this->addChild(effectGrid, GAME_STOP_LEVEL+1);
    gameRestartFUNC();
    this->getChildByTag(4)->setVisible(true);
}
void ShootBubbleLayer::removeNodeGird()
{
    this->removeChild(effectGrid);
}
void ShootBubbleLayer::gameRestartFUNC()
{
   
    Director* director = Director::getInstance();
    auto sched = director->getScheduler();
    sched->resumeTarget(this);
    FSLabel->setString("0");
    timeScore=-1;
    FSLabel->runAction(Sequence::create(MoveTo::create(1,Point(400,930)),ScaleTo::create(1,1),NULL));
    MAXHeight=850;
    Row=0;
    Col=0;
    initLocation();
    IsGameOver=false;

    std::vector<Sprite*>::iterator tempBall;
    for(tempBall = allBall->begin();tempBall!= allBall->end();tempBall++)
    {
        this->removeChild(*tempBall,true);
    }

    allBall->clear();

    this->removeChild(ballNextStart,true);

    this->removeChild(ballStart,true);

    this->removeChildByTag(GOTAG);
    this->removeChildByTag(77);
    for(int i=0;i<5;i++)
    {
        no[i]->setVisible(false);
    }
    this->removeChildByTag(101);
//      删除记分板
    this->removeChildByTag(100);

    intiBall();

    initIsEmpty();

    copyIsEmpty();

    drawBall();
    if(compressor!=NULL)
    {
        this->removeChildByTag(50);
        this->removeChildByTag(51);
        this->removeChildByTag(52);
        auto director = Director::getInstance();
        auto sched = director->getScheduler();
        sched->resumeTarget(this);
    }
    
    effectGrid->removeAllChildren();
    for(int i=0;i<14;i++)
    {
        for(int j=0;j<9;j++)
        {
            if (IsEmptyTemp[i][j]==0){
                continue;
            }
            Sprite* sp=Sprite::createWithTexture(Director::getInstance()->getTextureCache()
                                                 ->addImage(StringUtils::format("pic/ball_%d.png",IsEmptyTemp[i][j])));
            sp->cocos2d::Node::setPosition(bLocation[i][j]);
            effectGrid->addChild(sp,GAME_STOP_LEVEL+1);
        }
    }
    effectGrid->runAction(Sequence::create(
                                           ShuffleTiles::create(1.0f, Size(100,100), 25)->reverse(),
                                           CallFunc::create(CC_CALLBACK_0(ShootBubbleLayer::removeNodeGird,this)),
                                           NULL));
    if(StartLayer::soundB)
    {
       CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/game_scene_bg.mp3",true);
    }

}
//排行榜
void ShootBubbleLayer::phbMenu()
{
    int gk=ChooseGKLayer::gk;
    int pInt=10000;
    for(int i=gk*5-5;i<gk*5;i++)
    {
        pInt=UserDefault::getInstance()->getIntegerForKey(StringUtils::format("no%d",i).c_str());
        if(pInt==0)
        {
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",i).c_str(),timeScore);
            break;
        }
        if(timeScore==pInt)
        {
            break;
        }
        if(timeScore<pInt)
        {
            for(int j=gk*5-1;j>i;j--)
            {
                UserDefault::getInstance()->setIntegerForKey(
                                    StringUtils::format("no%d",j).c_str(),
                                    UserDefault::getInstance()->getIntegerForKey(StringUtils::format("no%d",j-1).c_str()));
            }
            UserDefault::getInstance()->setIntegerForKey(StringUtils::format("no%d",i).c_str(),timeScore);
            break;
        }
    }

    no[4]->runAction(Sequence::create(MoveTo::create(0.5,Point(300,300)),MoveTo::create(0.5,Point(300,290)),NULL));
    no[3]->runAction(Sequence::create(MoveTo::create(0.5,Point(300,340)),MoveTo::create(0.5,Point(300,370)),NULL));
    no[2]->runAction(Sequence::create(MoveTo::create(0.5,Point(300,380)),MoveTo::create(0.5,Point(300,450)),NULL));
    no[1]->runAction(Sequence::create(MoveTo::create(0.5,Point(300,410)),MoveTo::create(0.5,Point(300,535)),NULL));
    no[0]->runAction(Sequence::create(MoveTo::create(0.5,Point(300,450)),MoveTo::create(0.5,Point(300,620)),NULL));

    Sprite* ss=Sprite::create("pic/Score.png");
    ss->setPosition(Point(270,480));
    this->addChild(ss,DASHBOARD_LEVEL,100);
    
    for (int i=0; i<5; i++)
    {
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
        no[i]->setVisible(true);
        no[i]->setString(st);
    }
}
