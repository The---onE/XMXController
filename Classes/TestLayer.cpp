#include "TestLayer.h"

#define GROUND_HIGH 150*PARAM

using namespace XMX;

bool TestLayer::init()
{
	c = Sprite::create("r.png");
	c->setPosition(visibleSize.width/2, visibleSize.height/2);
	c->setScale(visibleSize.height/c->getContentSize().height*(0.2));
	addChild(c);

 	ControlBarX::setControler(Sprite::create("bar.png"), Sprite::create("ball.png"), 0.05f, 0.2f);
	ControlBarX::setTouchRect(Rect(0, 0, visibleSize.width/2, visibleSize.height));
 	ControlBarX::setSpeedMax(10);

 	Controller::setControler(Sprite::create("round.png"), Sprite::create("ball.png"), 0.1f, 0.025f);
	Controller::setTouchRect(Rect(visibleSize.width/2, 0, visibleSize.width/2, visibleSize.height));
 	Controller::setSpeedMax(10);
	Controller::set8DirectionMode(false);
	Controller::set4DirectionMode(false);
 
 	JumpButton::setJumpButton(Sprite::create("r.png"), 0.36f, visibleSize.width*0.8, visibleSize.height*0.2);
 	JumpButton::setJumpSpeed(24);
 	JumpButton::setGravity(0.8f, 1.2f);

	JumpGesture::setJumpButton(Rect(visibleSize.width/2, 0, visibleSize.width/2, visibleSize.height));
	JumpGesture::setJumpSpeed(24);
	JumpGesture::setGravity(0.8f, 1.2f);
	JumpGesture::setSensitivity(15);

	Button::addButton(10, Sprite::create("JumpGesture.png"), 0.06f, visibleSize.width*0.75, visibleSize.height*0.85);
	Button::addButton(11, Sprite::create("JumpButton.png"), 0.06f, visibleSize.width*0.75, visibleSize.height*0.75);
	Button::addButton(12, Sprite::create("Controller.png"), 0.06f, visibleSize.width*0.75, visibleSize.height*0.65);
	Button::addButton(20, Sprite::create("Vibrator60s.png"), 0.06f, visibleSize.width*0.1, visibleSize.height*0.85);
	Button::addButton(21, Sprite::create("CancelVibrate.png"), 0.06f, visibleSize.width*0.3, visibleSize.height*0.85);
	Button::addButton(22, Sprite::create("OpenVibrate.png"), 0.06f, visibleSize.width*0.1, visibleSize.height*0.75);
	Button::addButton(23, Sprite::create("CloseVibrate.png"), 0.06f, visibleSize.width*0.3, visibleSize.height*0.75);
	Button::addButton(30, Sprite::create("8DirectionMode.png"), 0.06f, visibleSize.width*0.1, visibleSize.height*0.65);
	Button::addButton(31, Sprite::create("4DirectionMode.png"), 0.06f, visibleSize.width*0.3, visibleSize.height*0.65);
	Button::addButton(32, Sprite::create("AllDirectionMode.png"), 0.06f, visibleSize.width*0.1, visibleSize.height*0.55);

	g2(); v2(); d2();
	buttonFlag = true;

	scheduleUpdate();

	return true;
}

void TestLayer::g0(){ Controller::notAllowControl(); JumpButton::hiddenButton();  JumpButton::forbidden(); JumpGesture::allowJump(); }
void TestLayer::g1(){ Controller::notAllowControl(); JumpButton::showButton();    JumpButton::allowJump(); JumpGesture::forbidden(); }
void TestLayer::g2(){ Controller::allowControl();    JumpButton::hiddenButton();  JumpButton::forbidden(); JumpGesture::forbidden(); }
void TestLayer::v0(){ Vibrator::vibrate(600000); }
void TestLayer::v1(){ Vibrator::cancelVibrate(); }
void TestLayer::v2(){ ControlBarX::setVibratorTime(VIBRATE_TIME); Controller::setVibratorTime(VIBRATE_TIME); JumpGesture::setVibratorTime(VIBRATE_TIME); JumpButton::setVibratorTime(VIBRATE_TIME); Button::setVibratorTime(VIBRATE_TIME); }
void TestLayer::v3(){ ControlBarX::setVibratorTime(0);  Controller::setVibratorTime(0);  JumpGesture::setVibratorTime(0);  JumpButton::setVibratorTime(0);  Button::setVibratorTime(0); }
void TestLayer::d0(){ Controller::set8DirectionMode(true); }
void TestLayer::d1(){ Controller::set4DirectionMode(true); }
void TestLayer::d2(){ Controller::set4DirectionMode(false); Controller::set8DirectionMode(false); }

void TestLayer::onEnter()
{
	Layer::onEnter();

 	auto listener = EventListenerTouchOneByOne::create();
 	listener->setSwallowTouches(false);
 	listener->onTouchBegan = CC_CALLBACK_2(TestLayer::onTouchBegan, this);
 	listener->onTouchMoved = CC_CALLBACK_2(TestLayer::onTouchMoved, this);
 	listener->onTouchEnded = CC_CALLBACK_2(TestLayer::onTouchEnded, this);
 	listener->onTouchCancelled = CC_CALLBACK_2(TestLayer::onTouchEnded, this);
 	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool TestLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	buttonFlag = Button::onTouchBegan(touch, unused_event);
	if (buttonFlag)
	{
		JumpButton::onTouchBegan(touch, unused_event);
		JumpGesture::onTouchBegan(touch, unused_event);
		ControlBarX::onTouchBegan(touch, unused_event);
		Controller::onTouchBegan(touch, unused_event);
	}

	return true;
}

void TestLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	JumpButton::onTouchMoved(touch, unused_event);
	if (buttonFlag)
	{
		JumpButton::onTouchMoved(touch, unused_event);
		JumpGesture::onTouchMoved(touch, unused_event);
		ControlBarX::onTouchMoved(touch, unused_event);
		Controller::onTouchMoved(touch, unused_event);
	}
}

void TestLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	Button::onTouchEnded(touch, unused_event);
	if (buttonFlag)
	{
		JumpButton::onTouchEnded(touch, unused_event);
		JumpGesture::onTouchEnded(touch, unused_event);
		ControlBarX::onTouchEnded(touch, unused_event);
		Controller::onTouchEnded(touch, unused_event);
	}
	buttonFlag = true;
}

void TestLayer::checkPress()
{
	if (Button::isNeedResponse(10))
	{
		g0();
		Button::responsed(10);
	}
	if (Button::isNeedResponse(11))
	{
		g1();
		Button::responsed(11);
	}
	if (Button::isNeedResponse(12))
	{
		g2();
		Button::responsed(12);
	}
	if (Button::isNeedResponse(20))
	{
		v0();
		Button::responsed(20);
	}
	if (Button::isNeedResponse(21))
	{
		v1();
		Button::responsed(21);
	}
	if (Button::isNeedResponse(22))
	{
		v2();
		Button::responsed(22);
	}
	if (Button::isNeedResponse(23))
	{
		v3();
		Button::responsed(23);
	}
	if (Button::isNeedResponse(30))
	{
		d0();
		Button::responsed(30);
	}
	if (Button::isNeedResponse(31))
	{
		d1();
		Button::responsed(31);
	}
	if (Button::isNeedResponse(32))
	{
		d2();
		Button::responsed(32);
	}
}

void TestLayer::update(float dt)
{
 	c->setPositionX(c->getPositionX() + ControlBarX::getSpeed());
 	c->setPositionX(c->getPositionX() + Controller::getSpeedX());
 	c->setPositionY(c->getPositionY() + Controller::getSpeedY());
 	c->setPositionY(c->getPositionY() + JumpButton::getSpeedY());
	c->setPositionY(c->getPositionY() + JumpGesture::getSpeedY());
	JumpButton::gravityEffect();
	JumpGesture::gravityEffect();
	checkPress();
 
 	Point p = c->getPosition();
 	if (p.x < 0)
 		c->setPositionX(0);
 	else if (p.x > WIDTH)
 		c->setPositionX(WIDTH);
 	if (p.y < 0)
 		c->setPositionY(0);
 	if (p.y >visibleSize.height)
 		c->setPositionY(visibleSize.height);
 
 	if (p.y < GROUND_HIGH)
 	{
 		JumpButton::resumeJump();
		JumpGesture::resumeJump();
 		c->setPositionY(GROUND_HIGH+FLT_EPSILON);
	}
}
