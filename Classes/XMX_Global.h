#pragma once

#include "cocos2d.h"
USING_NS_CC;
#include "XMX_Vibrator.h" //����

extern Size visibleSize;
extern Point origin; //Ӧ��AppDelegate.cpp�ж���ȫ�ֱ���������applicationDidFinishLaunching()�г�ʼ��
//visibleSize = Director::getInstance()->getVisibleSize();
//origin = Director::getInstance()->getVisibleOrigin();

#define WIDTH visibleSize.width //��Ļ���
#define HEIGHT visibleSize.height //��Ļ�߶�

#define DATUM visibleSize.height //���Ȼ�׼
#define SETSIZE(SPRITE,SIZE) ((SPRITE)->setScale(DATUM*(SIZE)/(SPRITE)->getContentSize().height)) //ΪSprite����������ڳ��Ȼ�׼�Ĵ�С
#define DEFAULT_WIDTH 1080 //Ĭ����Ļ���
#define PARAM  (DATUM/DEFAULT_WIDTH) //�ٶȱ�׼������

#define VIBRATE_TIME 48 //��ʱ��
#define NOANGLE -1800 //δ�϶�������


/*#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
	keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this); \
	keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this); \
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
