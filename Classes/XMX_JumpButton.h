#pragma once

/****************************************************************************
//调用 setJumpButton 设置跳跃按钮
//调用 hiddenButton 隐藏按钮
//调用 showButton 显示按钮
//调用 setJumpSpeed 设置跳跃速度
//调用 setVibratorTime 设置震动时间
//调用 allowJump 设置为允许触控
//调用 notAllowJump 设置为不允许触控
//调用 forbidden 设置禁止跳跃（物体不再受重力影响，纵向速度消失）
//调用 setGravity 设置重力
//调用 getSpeedY 获得速度（应在子类 update 中设置 c->setPositionY(c->getPositionY() + getSpeedY())）
//调用 resume 恢复为未跳跃状态（落地时调用）
//调用 gravityEffect 每帧使物体受重力的影响（应加入子类 update 中）
//将 onTouchBegan onTouchMoved onTouchEnded 添加至子类对应函数中
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	class JumpButton : public virtual Layer
	{
	private:
		int vibratorTime; //震动时间
		float jumpSpeed; //跳跃速度
		float speedY; //纵向瞬时速度
		float gravity; //当前重力大小
		float lowGravity; //低重力状态重力大小
		float highGravity; //高重力状态重力大小
		Sprite* jumpButton; //跳跃按钮Sprite
		Rect jumpRect; //响应触控的区域
		bool touchFlag; //是否已被按下
		bool allowJumpFlag; //是否允许跳跃
		bool allowJumpTwiceFlag; //是否允许二段跳
		bool jumpOnceFlag; //是否已跳跃一次
		bool jumpTwiceFlag; //是否已跳跃两次
		bool highGravityFlag; //是否为高重力模式
		bool gravityEffectFlag; //是否受到重力影响
		bool jumpButtonFlag; //是否已设置跳跃按钮
		bool jumpSpeedFlag; //是否已设置跳跃速度

		bool checkControler(); //检查跳跃按钮是否已被成功设置
		void setHighGravity(); //设置为高重力模式（跳跃上升阶段松开跳跃按钮的重力）
		void setLowGravity(); //设置为低重力模式（未跳跃或跳跃上升阶段按住跳跃按钮或跳跃下落阶段的重力）
		void jumpBegan(); //跳跃开始
		void jumpEnded(); //跳跃结束

	public:
		JumpButton();
		void setJumpButton(Sprite* jumpButton, float size, int x, int y); //通过Sprite设置跳跃按钮
		void setJumpButton(Rect jumpRect); //通过矩形设置跳跃按钮
		bool hiddenButton(); //隐藏按钮
		bool showButton(); //显示按钮
		void setJumpSpeed(float jumpSpeed); //设置跳跃速度
		void setVibratorTime(int time); //设置震动时间
		void allowJump(); //设置为允许跳跃
		void notAllowJump(); //设置为不允许跳跃（重力不变）
		void forbidden(); //设置为禁止跳跃（物体不再受重力影响，纵向速度消失）
		void setGravity(float gravity); //设置重力（低、高重力相同）
		void setGravity(float lowGravity, float highGravity); //设置重力（分别设置低、高重力）
		float getSpeedY(); //获得纵向速度
		void resumeJump(); //恢复为未跳跃状态（落地时调用）
		void gravityEffect(); //每帧使物体受重力的影响（应加入子类update函数中）
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
