#include "XMX_JumpButton.h"

using namespace XMX;

JumpButton::JumpButton()
{
	jumpButton = NULL;
	jumpRect = Rect();

	speedY = 0;
	jumpSpeed = 0;
	gravity = 0;
	lowGravity = 0;
	highGravity = 0;

	vibratorTime = VIBRATE_TIME;

	jumpButtonFlag = false;
	touchFlag = false;
	allowJumpFlag = true;
	allowJumpTwiceFlag = true;
	jumpOnceFlag = false;;
	jumpTwiceFlag = false;
	highGravityFlag = false;
	jumpSpeedFlag = false;
	gravityEffectFlag = false;
}

void JumpButton::setJumpButton(Sprite* jumpButton, float size, int x, int y)
{
	removeChild(this->jumpButton);

	this->jumpButton = jumpButton;
	SETSIZE(this->jumpButton, size);
	this->jumpButton->setPosition(Point(x,y));
	addChild(this->jumpButton);

	this->jumpRect = jumpButton->getBoundingBox();

	this->jumpButtonFlag = true;
}

void JumpButton::setJumpButton(Rect jumpRect)
{
	this->jumpRect = jumpRect;

	this->jumpButtonFlag = true;
}

bool JumpButton::hiddenButton()
{
	if (!jumpButton)
	{
		return false;
	}
	jumpButton->setVisible(false);
	notAllowJump();
	return true;
}

bool JumpButton::showButton()
{
	if (!jumpButton)
	{
		return false;
	}
	jumpButton->setVisible(true);
	allowJump();
	return true;
}

void JumpButton::setJumpSpeed(float jumpSpeed)
{
	this->jumpSpeed = jumpSpeed * PARAM;

	this->jumpSpeedFlag = true;
}

void JumpButton::setVibratorTime(int time)
{
	vibratorTime = time;
}

void JumpButton::allowJump()
{
	allowJumpFlag = true;
	gravityEffectFlag = true;
}

void JumpButton::notAllowJump()
{
	allowJumpFlag = false;
}

void JumpButton::forbidden()
{
	notAllowJump();
	gravityEffectFlag = false;
	resumeJump();
}

void JumpButton::setGravity(float gravity)
{
	this->lowGravity = gravity * PARAM;
	this->highGravity = gravity * PARAM;

	this->gravity = gravity * PARAM;
}

void JumpButton::setGravity(float lowGravity, float highGravity)
{
	this->lowGravity = lowGravity * PARAM;
	this->highGravity = highGravity * PARAM;

	this->gravity = lowGravity * PARAM;
}

float JumpButton::getSpeedY()
{
	return speedY;
}

bool JumpButton::checkControler()
{
	if (!jumpButtonFlag)
		return false;
	if (!jumpSpeedFlag)
		return false;

	return true;
}

void JumpButton::gravityEffect()
{
	if (gravityEffectFlag)
	{
		speedY -= gravity;
		if (highGravityFlag)
		{
			if (speedY < 0)
			{
				setLowGravity();
			}
		}
	}
}

void JumpButton::resumeJump()
{
	speedY = 0;
	jumpOnceFlag = false;
	jumpTwiceFlag = false;

	setLowGravity();
}

void JumpButton::jumpBegan()
{
	if (!jumpOnceFlag && !jumpTwiceFlag)
	{
		Vibrator::vibrate(vibratorTime);

		speedY = jumpSpeed;
		jumpOnceFlag = true;
		setLowGravity();
	}
	else if (jumpOnceFlag && !jumpTwiceFlag && allowJumpTwiceFlag)
	{
		Vibrator::vibrate(vibratorTime);

		speedY = jumpSpeed;
		jumpTwiceFlag = true;
		setLowGravity();
	}
}

void JumpButton::jumpEnded()
{
	setHighGravity();
}

bool JumpButton::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (allowJumpFlag)
	{
		if (!touchFlag)
		{
			if (checkControler())
			{
				Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
				if (jumpRect.containsPoint(touchPoint))
				{
					jumpBegan();
					touchFlag = true;
				}

			}
		}
	}
	return true;
}

void JumpButton::onTouchMoved(Touch *touch, Event *unused_event)
{
}

void JumpButton::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (allowJumpFlag)
	{
		if (touchFlag)
		{
			Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());

			if (jumpRect.containsPoint(startPoint))
			{
				jumpEnded();
				touchFlag = false;
			}
		}
	}
}

void JumpButton::setHighGravity()
{
	gravity = highGravity;
	highGravityFlag = true;
}

void JumpButton::setLowGravity()
{
	gravity = lowGravity;
	highGravityFlag = false;
}