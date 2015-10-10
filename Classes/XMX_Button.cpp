#include "XMX_Button.h"

using namespace XMX;

Button::Button()
{
	vibratorTime = VIBRATE_TIME;
}

bool Button::addButton(int id, Button_Node* adding)
{
	list.insert(id, adding);

	return true;
}

bool Button::addButton(int id, Sprite* button, float size, int x, int y, float anchorX /* = 0.5 */, float anchorY /* = 0.5 */, Method press /* = NULL */, Method release /* = NULL */)
{
	Button_Node* adding = Button_Node::create();
	SETSIZE(button, size);
	button->setAnchorPoint(Point(anchorX, anchorY));
	button->setPosition(Point(x,y));
	adding->button = button;
	addChild(adding->button);
	adding->rect = button->getBoundingBox();
	adding->onPress = press;
	adding->onRelease = release;
	adding->buttonFlag = true;
	adding->allowFlag = true;

	return addButton(id, adding);
}

bool Button::addButton(int id, Rect rect, Method press/* =NULL */, Method release/* =NULL */)
{
	Button_Node* adding = Button_Node::create();
	adding->rect = rect;
	adding->onPress = press;
	adding->onRelease = release;
	adding->buttonFlag = true;
	adding->allowFlag = true;

	return addButton(id, adding);
}

bool Button::changeButton(int id, Sprite* button, float size, int x, int y, float anchorX /* = 0.5 */, float anchorY /* = 0.5 */)
{
	Button_Node* p = searchButton(id);
	if (!p)
	{
		addButton(id, button, size, x, y);
	}
	else
	{
		removeChild(p->button);
		SETSIZE(button, size);
		button->setAnchorPoint(Point(anchorX, anchorY));
		button->setPosition(Point(x,y));
		p->button = button;
		addChild(p->button);
		p->rect = button->getBoundingBox();
	}
	return true;
}

bool Button::removeButton(int id)
{
	Button_Node* p = searchButton(id);
	if (!p)
	{
		return false;
	}
	else
	{
		removeChild(p->button);
		list.erase(id);
	}
	return true;
}

bool Button::hiddenButton(int id)
{
	Button_Node* p = searchButton(id);
	if (!p)
	{
		return false;
	}
	else
	{
		p->button->setVisible(false);
		forbidden(id);
	}
	return true;
}

bool Button::showButton(int id)
{
	Button_Node* p = searchButton(id);
	if (!p)
	{
		return false;
	}
	else
	{
		if (!(p->button))
		{
			allow(id);
			return false;
		}
		p->button->setVisible(true);
		allow(id);
	}
	return true;
}

void Button::setData(int id, int index, int data)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		p->data[index] =  data;
	}
}

int Button::getData(int id, int index)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		return p->data.at(index);
	}
	return 0;
}

Button_Node* Button::searchButton(int id)
{
	Button_Node* p = list.at(id);
	return p;
}

void Button::setVibratorTime(int time)
{
	vibratorTime = time;
}

void Button::allow(int id)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		p->allowFlag = true;
	}
}

void Button::forbidden(int id)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		p->allowFlag = false;
	}
}

bool Button::isNeedResponse(int id)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		return p->needResponseFlag;
	}
	return false;
}

void Button::needResponse(int id)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		p->needResponseFlag = true;
	}
}

void Button::responsed(int id)
{
	Button_Node* p = searchButton(id);
	if (p)
	{
		p->needResponseFlag = false;
	}
}

bool Button::onTouchBegan(Touch *touch, Event *unused_event)
{
	bool flag = true;
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	Map<int, Button_Node*>::iterator it = list.begin();
	while (it != list.end())
	{
		Button_Node* p = it->second;
		if (p->allowFlag)
		{
			if (!p->touchFlag)
			{
				if (p->buttonFlag)
				{
					if (p->rect.containsPoint(touchPoint))
					{
						Vibrator::vibrate(vibratorTime);
						Method method = p->onPress;
						if (method)
						{
							method();
						}
						else
						{
							p->needResponseFlag = true;
						}
						p->touchFlag = true;
						flag = false;
					}
				}
			}
		}
		it++;
	}
	return flag;
}

void Button::onTouchMoved(Touch *touch, Event *unused_event)
{
}

void Button::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	Point startPoint = Director::getInstance()->convertToGL(touch->getStartLocationInView());
	Map<int, Button_Node*>::iterator it = list.begin();
	while (it != list.end())
	{
		Button_Node* p = it->second;
		if (p->allowFlag)
		{
			if (p->touchFlag)
			{
				if (p->rect.containsPoint(startPoint))
				{
					if (p->rect.containsPoint(touchPoint))
					{
						Method method = p->onRelease;
						if (method)
						{
							method();
						}
					}
					p->touchFlag = false;
				}
			}
		}
		it++;
	}
}