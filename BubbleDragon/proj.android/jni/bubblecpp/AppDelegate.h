#ifndef  _AppDelegate_H_
#define  _AppDelegate_H_
#include "cocos2d.h"
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();//构造函数
    virtual ~AppDelegate();//析构函数
    virtual bool applicationDidFinishLaunching();//程序初始化
    virtual void applicationDidEnterBackground();//程序进入后台
    virtual void applicationWillEnterForeground();//程序进入前台
};
#endif

