#pragma once

/****************************************************************************
//调用 XMX_Button_addButton 添加按钮
//调用 XMX_Button_changeButton 更改按钮图标
//调用 XMX_Button_removeButton 移除按钮
//调用 XMX_Button_hiddenButton 隐藏按钮
//调用 XMX_Button_showButton 显示按钮
//调用 XMX_Button_setData 添加/修改数据
//调用 XMX_Button_getData 获得数据
//调用 XMX_Button_setVibratorTime 设置震动时间
//调用 XMX_Button_allow 允许使用按钮
//调用 XMX_Button_forbidden 禁止使用按钮
//调用 XMX_Button_isNeedResponse 判断是否需要响应(应在update中判断，并在做出反应后调用 XMX_Button_responsed)
//将 XMX_Button_onTouchBegan XMX_Button_onTouchMoved XMX_Button_onTouchEnded 添加至子类对应函数中
//若要使按钮阻断触控传递，判断 XMX_Button_onTouchBegan 的返回值，为true则未触控到，为false则触控到
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	typedef bool(*Method)();
	class Button_Node : public Node //按钮节点
	{
	public:
		Sprite* button; //按钮显示的Sprite
		Rect rect; //响应触控的区域
		Method onPress; //当按钮按下时触发的函数
		Method onRelease; //当按钮松开时触发的函数
		bool buttonFlag; //按钮是否已被初始化
		bool touchFlag; //按钮是否被按下
		bool allowFlag; //按钮是否允许使用
		bool needResponseFlag; //是否需要响应
		std::map<int, int> data; //预留数据空间

		CREATE_FUNC(Button_Node);
		bool init()
		{
			button = NULL;
			rect = Rect();
			onPress = NULL;
			onRelease = NULL;
			buttonFlag = false;
			touchFlag = false;
			allowFlag = false;
			needResponseFlag = false;

			return true;
		}
	};

	class Button : public virtual Layer
	{
	private:
		int vibratorTime;
		Map<int, Button_Node*> list;

		Button_Node* searchButton(int id);
		bool addButton(int id, Button_Node* adding);
		void needResponse(int id);

	public:
		Button();
		bool addButton(int id, Sprite* button, float size, int x, int y, float anchorX = 0.5, float anchorY = 0.5, Method press = NULL, Method release = NULL); //通过Sprite添加按钮
		bool addButton(int id, Rect rect, Method press = NULL, Method release = NULL); //通过矩形添加按钮
		bool changeButton(int id, Sprite* button, float size, int x, int y, float anchorX = 0.5, float anchorY = 0.5); //通过Sprite更改按钮图标
		bool removeButton(int id); //移除按钮
		bool hiddenButton(int id); //隐藏按钮
		bool showButton(int id); //显示按钮
		void setData(int id, int index, int data); //添加/修改数据
		int getData(int id, int index); //获得数据
		void setVibratorTime(int time); //设置震动时间
		void allow(int id); //设置为允许使用
		void forbidden(int id); //设置为禁止使用
		bool isNeedResponse(int id); //判断是否需要响应
		void responsed(int id); //响应按钮
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
