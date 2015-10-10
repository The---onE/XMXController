#pragma once

/****************************************************************************
//调用 setControler 设置控制球
//调用 setSpeedMax 设置最大速度
//调用 setTouchRect 设置触控区域
//调用 setVibratorTime 设置震动时间
//调用 set4DirectionMode 设置为四方向模式
//调用 set8DirectionMode 设置为八方向模式
//调用 allowControl 设置为允许触控
//调用 notAllowControl 设置为不允许触控
//调用 getSpeedX getSpeedY 获得瞬时速度（应在子类 update 中设置 c->setPositionX(c->getPositionX() + getSpeedX()) c->setPositionY(c->getPositionY() + getSpeedY())）
//将 onTouchBegan onTouchMoved onTouchEnded 添加至子类对应函数中
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	class Controller : public virtual Layer
	{
	private:
		int vibratorTime; //震动时间
		int angleLevel; //触控点所在角度区域
		float rb; //控制球半径
		float rs; //触控点半径
		float speedX; //横向瞬时速度
		float speedY; //纵向瞬时速度
		float speedMax; //最大速度（拉至触控球边缘）
		int angle; //相对水平方向角度
		Rect touchRect; //响应触控的区域（开始触控）
		Sprite* round; //控制球Sprite
		Sprite* ball; //触控点Sprite
		bool touchFlag; //是否已开始触控
		bool allowControlFlag; //是否允许触控
		bool touchMaxFlag; //是否已拉至边缘
		bool _8directionFlag; //是否为八方向模式
		bool _4directionFlag; //是否为四方向模式
		bool controlerFlag; //是否设置控制球
		bool speedMaxFlag; //是否已设置最大速度
		bool touchRectFlag; //是否已设置触控区域

		bool checkControler(); //检查控制球是否已被成功设置

	public:
		Controller();
		void setControler(Sprite* round, Sprite* ball, float rb, float rs); //设置控制球
		void setSpeedMax(float speedMax); //设置最大速度
		void setTouchRect(Rect touchRact); //设置触控区域
		void setVibratorTime(int time); //设置震动时间
		void set4DirectionMode(bool flag); //设置为四方向模式
		void set8DirectionMode(bool flag); //设置为八方向模式
		void allowControl(); //设置为允许触控
		void notAllowControl(); //设置为不允许触控
		float getSpeedX(); //获得横向瞬时速度
		float getSpeedY(); //获得纵向瞬时速度
		int getAngle(); //获得相对水平方向角度
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
