#pragma once

/****************************************************************************
//调用 setControler 设置控制条
//调用 setSpeedMax 设置最大速度
//调用 setTouchRect 设置触控区域
//调用 setVibratorTime 设置震动时间
//调用 allowControl 设置为允许触控
//调用 notAllowControl() 设置为不允许触控
//调用 getSpeed 获得瞬时速度（应在子类 update 中设置 c->setPositionX(c->getPositionX() + getSpeed())）
//将 onTouchBegan onTouchMoved onTouchEnded 添加至子类对应函数中
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	class ControlBarX : public virtual Layer
	{
	private:
		int vibratorTime; //震动时间
		float height; //控制条高度
		float width; //控制条宽度
		float speed; //瞬时速度
		float speedMax; //最大速度（拉至控制条两端时）
		Rect touchRect; //响应触控的区域（开始触控）
		Sprite* bar; //控制条Sprite
		Sprite* ball; //触控点Sprite
		bool touchFlag; //是否已开始触控
		bool allowControlFlag; //是否允许触控
		bool touchMaxFlag; //是否已拉至控制条两端
		bool leftFlag; //触控点是否在左端（切换左右端时震动）
		bool rightFlag; //触控点是否在右端（切换左右端时震动）
		bool controlerFlag; //是否已设置控制条
		bool speedMaxFlag; //是否已设置最大速度
		bool touchRectFlag; //是否已设置触控区域

		bool checkControler(); //检查控制条已被成功设置

	public:
		ControlBarX();
		bool setControler(Sprite* bar, Sprite* ball, float height, float width); //设置控制条
		bool setSpeedMax(float speedMax); //设置最大速度
		bool setTouchRect(Rect touchRect); //设置触控区域
		void setVibratorTime(int time); //设置震动时间
		void allowControl(); //设置为允许触控
		void notAllowControl(); //设置为不允许触控
		float getSpeed(); //获得瞬时速度
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
