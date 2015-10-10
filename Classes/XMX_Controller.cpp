#include "XMX_Controller.h"

using namespace XMX;

Controller::Controller()
{
	rb = 0;
	rs = 0;

	touchRect = Rect();
	round = NULL;
	ball = NULL;

	speedX = 0;
	speedY = 0;
	speedMax = 0;

	angleLevel = -1;
	angle = NOANGLE;

	vibratorTime = VIBRATE_TIME;

	touchRectFlag = false;
	touchFlag = false;
	speedMaxFlag = false;
	controlerFlag = false;
	allowControlFlag = true;
	touchMaxFlag = false;
	_8directionFlag = false;
	_4directionFlag = false;
}

bool Controller::checkControler()
{
	if (!controlerFlag)
		return false;
	if (!speedMaxFlag)
		return false;
	if (!touchRectFlag)
		return false;

	return true;
}

void Controller::setControler(Sprite* round, Sprite* ball, float rb, float rs)
{
	removeChild(this->round);
	removeChild(this->ball);

	this->round = round;
	this->ball = ball;
	this->rb = rb;
	this->rs = rs;

	SETSIZE(this->round, this->rb*2);
	SETSIZE(this->ball, this->rs*2);

	this->round->setPosition(Point::ZERO);
	this->round->setVisible(false);
	this->ball->setPosition(Point::ZERO);
	this->ball->setVisible(false);

	addChild(this->round);
	addChild(this->ball);

	this->controlerFlag = true;
}

void Controller::setSpeedMax(float speedMax)
{
	this->speedMax = speedMax * PARAM;
	this->speedMaxFlag = true;
}

void Controller::setVibratorTime(int time)
{
	vibratorTime = time;
}

void Controller::set4DirectionMode(bool flag)
{
	_4directionFlag = flag;
	if (flag)
		_8directionFlag = false;
}

void Controller::set8DirectionMode(bool flag)
{
	_8directionFlag = flag;
	if (flag)
		_4directionFlag = false;
}

void Controller::allowControl()
{
	allowControlFlag = true;
}

void Controller::notAllowControl()
{
	allowControlFlag = false;

	round->setVisible(false);
	ball->setVisible(false);
	speedX = 0;
	speedY = 0;
	angleLevel = -1;
	touchFlag = false;
	touchMaxFlag = false;
}

void Controller::setTouchRect(Rect touchRact)
{
	this->touchRect = touchRact;

	this->touchRectFlag = true;
}

bool Controller::onTouchBegan(Touch *touch, Event *unused_event)
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

					round->setPosition(touchPoint);
					round->setVisible(true);
					ball->setPosition(touchPoint);
					ball->setVisible(true);

					touchFlag = true;
				}
			}
		}
	}
	return true;
}

void Controller::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (allowControlFlag)
	{
		if (touchFlag)
		{
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
			Point sourcePoint = round->getPosition();
			if (startPoint.equals(sourcePoint))
			{
				Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
				int d = sourcePoint.getDistance(touchPoint);
				float angle = atan2(touchPoint.y-sourcePoint.y, touchPoint.x-sourcePoint.x);

				if (d > rb*DATUM)
				{
					d = rb*DATUM;
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

				if (_8directionFlag)
				{
					int angleLevel = (angle / 3.1416 + 1.125) * 4;
					if (angleLevel >= 8)
						angleLevel = 0;
					if (this->angleLevel != angleLevel && this->angleLevel > -1 && d > this->rb*DATUM*0.5)
						Vibrator::vibrate(this->vibratorTime);
					this->angleLevel = angleLevel;
					angle = ((float)angleLevel / 4 - 1)*3.1416;
				}
				if (_4directionFlag)
				{
					int angleLevel = (angle / 3.1416 + 1.25) * 2;
					if (angleLevel >= 4)
						angleLevel = 0;
					if (this->angleLevel != angleLevel && this->angleLevel > -1 && d > this->rb*DATUM*0.5)
						Vibrator::vibrate(this->vibratorTime);
					this->angleLevel = angleLevel;
					angle = ((float)angleLevel / 2 - 1)*3.1416;
				}

				ball->setPosition(round->getPositionX()+d*cos(angle), round->getPositionY()+d*sin(angle));
				speedX = speedMax*d*cos(angle)/(DATUM*rb);
				speedY = speedMax*d*sin(angle)/(DATUM*rb);
				this->angle = MATH_RAD_TO_DEG(angle);
			}
		}
	}
}

void Controller::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (allowControlFlag)
	{
		if (touchFlag)
		{
			Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
			Point sourcePoint = round->getPosition();
			if (startPoint.equals(sourcePoint))
			{
				round->setVisible(false);
				ball->setVisible(false);
				speedX = 0;
				speedY = 0;

				angleLevel = -1;
				angle = NOANGLE;

				touchFlag = false;
				touchMaxFlag = false;
			}
		}
	}
}

float Controller::getSpeedX()
{
	return speedX;
}

float Controller::getSpeedY()
{
	return speedY;
}

int Controller::getAngle()
{
	return angle;
}