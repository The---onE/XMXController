#pragma once

#include "XMX_Global.h"

#include "XMX_ControlBarX.h"
#include "XMX_Controller.h"
#include "XMX_JumpButton.h"
#include "XMX_JumpGesture.h"
#include "XMX_Button.h"

class TestLayer : public XMX::ControlBarX, public XMX::Controller, public XMX::JumpButton, public XMX::JumpGesture, public XMX::Button
{
public:
	CREATE_FUNC(TestLayer);
	bool init();
	void onEnter();
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);
	void checkPress();
	void update(float dt);

	void g0();
	void g1();
	void g2();
	void v0();
	void v1();
	void v2();
	void v3();
	void d0();
	void d1();
	void d2();

	Sprite* c;
	bool buttonFlag;
};
