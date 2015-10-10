#include "XMX_JumpGesture.h"

using namespace XMX;

JumpGesture::JumpGesture()
{
	jumpRect = Rect();

	speedY = 0;
	jumpSpeed = 0;
	gravity = 0;
	lowGravity = 0;
	highGravity = 0;

	vibratorTime = 0;

	jumpButtonFlag = false;
	touchFlag = false;
	allowJumpFlag = true;
	allowJumpTwiceFlag = true;
	jumpOnceFlag = false;;
	jumpTwiceFlag = false;
	highGravityFlag = false;
	jumpSpeedFlag = false;
	sensitivityFlag = false;
	touchJumpFlag = false;
	gravityEffectFlag = true;
}

void JumpGesture::setJumpButton(Rect jumpRect)
{
	this->jumpRect = jumpRect;

	this->jumpButtonFlag = true;
}

void JumpGesture::setJumpSpeed(float jumpSpeed)
{
	this->jumpSpeed = jumpSpeed * PARAM;

	this->jumpSpeedFlag = true;
}

void JumpGesture::setSensitivity(int sensitivity)
{
	this->sensitivity = sensitivity * PARAM;

	this->sensitivityFlag = true;
}

void JumpGesture::setVibratorTime(int time)
{
	vibratorTime = time;
}

void JumpGesture::allowJump()
{
	allowJumpFlag = true;
	gravityEffectFlag = true;
}

void JumpGesture::notAllowJump()
{
	allowJumpFlag = false;
}

void JumpGesture::forbidden()
{
	notAllowJump();
	gravityEffectFlag = false;
	resumeJump();
}

void JumpGesture::setGravity(float gravity)
{
	this->lowGravity = gravity * PARAM;
	this->highGravity = gravity * PARAM;

	this->gravity = gravity * PARAM;
}

void JumpGesture::setGravity(float lowGravity, float highGravity)
{
	this->lowGravity = lowGravity * PARAM;
	this->highGravity = highGravity * PARAM;

	this->gravity = lowGravity * PARAM;
}

float JumpGesture::getSpeedY()
{
	return speedY;
}

bool JumpGesture::checkControler()
{
	if (!jumpButtonFlag)
		return false;
	if (!jumpSpeedFlag)
		return false;
	if (!sensitivityFlag)
		return false;

	return true;
}

void JumpGesture::gravityEffect()
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

void JumpGesture::resumeJump()
{
	speedY = 0;
	jumpOnceFlag = false;
	jumpTwiceFlag = false;

	setLowGravity();
}

bool JumpGesture::onTouchBegan(Touch *touch, Event *unused_event)
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
					sourcePoint = touchPoint;

					touchFlag = true;
					touchJumpFlag = false;
				}

			}
		}
	}
	return true;
}

void JumpGesture::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (allowJumpFlag)
	{
		if (touchFlag)
		{
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
			if (startPoint.equals(sourcePoint))
			{
				Point previousPoint = Director::getInstance()->convertToGL(touch->getPreviousLocationInView());
				Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
				if (touchPoint.y - previousPoint.y > sensitivity)
				{
					if (!touchJumpFlag && !jumpOnceFlag && !jumpTwiceFlag)
					{
						Vibrator::vibrate(vibratorTime);

						speedY = jumpSpeed;
						jumpOnceFlag = true;
						setLowGravity();

						touchJumpFlag = true;
					}
					else if (!touchJumpFlag && jumpOnceFlag && !jumpTwiceFlag && allowJumpTwiceFlag)
					{
						Vibrator::vibrate(vibratorTime);

						speedY = jumpSpeed;
						jumpTwiceFlag = true;
						setLowGravity();
					}
				}
			}
		}
	}
}

void JumpGesture::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (allowJumpFlag)
	{
		if (touchFlag)
		{
			Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());

			if (startPoint.equals(sourcePoint))
			{
				setHighGravity();

				touchFlag = false;
				touchJumpFlag = false;
			}
		}
	}
}

void JumpGesture::setHighGravity()
{
	gravity = highGravity;
	highGravityFlag = true;
}

void JumpGesture::setLowGravity()
{
	gravity = lowGravity;
	highGravityFlag = false;
}