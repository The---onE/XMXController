#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include "XMX_Vibrator.h" //震动器

extern Size visibleSize;
extern Point origin; //应在AppDelegate.cpp中定义全局变量，并在applicationDidFinishLaunching()中初始化
//visibleSize = Director::getInstance()->getVisibleSize();
//origin = Director::getInstance()->getVisibleOrigin();

#define WIDTH visibleSize.width //屏幕宽度
#define HEIGHT visibleSize.height //屏幕高度

#define DATUM visibleSize.height //长度基准
#define SETSIZE(SPRITE,SIZE) ((SPRITE)->setScale(DATUM*(SIZE)/(SPRITE)->getContentSize().height)) //为Sprite等设置相对于长度基准的大小
#define DEFAULT_WIDTH 1080 //默认屏幕宽度
#define PARAM  (DATUM/DEFAULT_WIDTH) //速度标准化参数

#define VIBRATE_TIME 48 //震动时间
#define NOANGLE -1800 //未拖动控制球


/*#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
	keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this); \
	keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this); \
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
