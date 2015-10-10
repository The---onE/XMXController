#include "XMX_ControlBarX.h"

using namespace XMX;

ControlBarX::ControlBarX()
{
	height = 0;
	width = 0;

	touchRect = Rect();
	bar = NULL;
	ball = NULL;

	speed = 0;
	speedMax = 0;

	vibratorTime = VIBRATE_TIME;

	touchRectFlag = false;
	touchFlag = false;
	speedMaxFlag = false;
	controlerFlag = false;
	allowControlFlag = true;
	touchMaxFlag = false;
	leftFlag = false;
	rightFlag = false;
}

bool ControlBarX::checkControler()
{
	if (!controlerFlag)
		return false;
	if (!speedMaxFlag)
		return false;
	if (!touchRectFlag)
		return false;

	return true;
}

bool ControlBarX::setControler(Sprite* bar, Sprite* ball, float height, float width)
{
	removeChild(this->bar);
	removeChild(this->ball);

	this->bar = bar;
	this->ball = ball;
	this->height = height;
	this->width = width;

	SETSIZE(this->bar, this->height);
	SETSIZE(this->ball, this->height);
	this->bar->setScaleX(DATUM* this->width/this->bar->getContentSize().width);

	this->bar->setPosition(Point::ZERO);
	this->bar->setVisible(false);
	this->ball->setPosition(Point::ZERO);
	this->ball->setVisible(false);

	addChild(this->bar);
	addChild(this->ball);

	this->controlerFlag = true;

	return true;
}

bool ControlBarX::setSpeedMax(float speedMax)
{
	this->speedMax = speedMax * PARAM;
	this->speedMaxFlag = true;

	return true;
}

bool ControlBarX::setTouchRect(Rect touchRect)
{
	this->touchRect = touchRect;

	this->touchRectFlag = true;

	return true;
}

void ControlBarX::setVibratorTime(int time)
{
	vibratorTime = time;
}

void ControlBarX::allowControl()
{
	allowControlFlag = true;
}

void ControlBarX::notAllowControl()
{
	allowControlFlag = false;

	bar->setVisible(false);
	ball->setVisible(false);
	speed = 0;
	touchFlag = false;
	touchMaxFlag = false;
	leftFlag = false;
	rightFlag = false;
}


bool ControlBarX::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (allowControlFlag)
	{
		if (!touchFlag)
		{
			if (checkControler())
			{
				Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
				if (touchRect.containsPoint(touchPoint))
				{
					Vibrator::vibrate(vibratorTime);

					bar->setPosition(touchPoint);
					bar->setVisible(true);
					ball->setPosition(touchPoint);
					ball->setVisible(true);

					touchFlag = true;
				}
			}
		}
	}
	return true;
}

void ControlBarX::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (allowControlFlag)
	{
		if (touchFlag)
		{
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
			Point sourcePoint = bar->getPosition();
			if (startPoint.equals(sourcePoint))
			{
				Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
				int delta = touchPoint.x - bar->getPositionX();

				if (delta > 0)
				{
					if (leftFlag && !rightFlag)
					{
						leftFlag = false;
						rightFlag = true;
						Vibrator::vibrate(vibratorTime);
					}
					leftFlag = false;
					rightFlag = true;

					if (delta > DATUM*width/2)
					{
						delta = DATUM*width/2;
						if (!touchMaxFlag)
						{
							touchMaxFlag = true;
							Vibrator::vibrate(vibratorTime);
						}
					}
					else
					{
						touchMaxFlag = false;
					}
				}
				else if (delta < 0)
				{
					if (rightFlag && !leftFlag)
					{
						rightFlag = false;
						leftFlag = true;
						Vibrator::vibrate(vibratorTime);
					}
					rightFlag = false;
					leftFlag = true;

					if (delta < -DATUM*width/2)
					{
						delta = -DATUM*width/2;
						if (!touchMaxFlag)
						{
							touchMaxFlag = true;
							Vibrator::vibrate(vibratorTime);
						}
					}
					else
					{
						touchMaxFlag = false;
					}
				}

				ball->setPositionX(bar->getPositionX() + delta);
				speed = speedMax * delta/(DATUM*width/2);
			}
		}
	}
}

void ControlBarX::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (allowControlFlag)
	{
		if (touchFlag)
		{
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
			Point sourcePoint = bar->getPosition();
			if (startPoint.equals(sourcePoint))
			{
				bar->setVisible(false);
				ball->setVisible(false);
				speed = 0;

				touchFlag = false;
				touchMaxFlag = false;
				leftFlag = false;
				rightFlag = false;
			}
		}
	}
}

float ControlBarX::getSpeed()
{
	return speed;
}