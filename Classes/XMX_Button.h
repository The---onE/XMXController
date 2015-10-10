#pragma once

/****************************************************************************
//���� XMX_Button_addButton ��Ӱ�ť
//���� XMX_Button_changeButton ���İ�ťͼ��
//���� XMX_Button_removeButton �Ƴ���ť
//���� XMX_Button_hiddenButton ���ذ�ť
//���� XMX_Button_showButton ��ʾ��ť
//���� XMX_Button_setData ���/�޸�����
//���� XMX_Button_getData �������
//���� XMX_Button_setVibratorTime ������ʱ��
//���� XMX_Button_allow ����ʹ�ð�ť
//���� XMX_Button_forbidden ��ֹʹ�ð�ť
//���� XMX_Button_isNeedResponse �ж��Ƿ���Ҫ��Ӧ(Ӧ��update���жϣ�����������Ӧ����� XMX_Button_responsed)
//�� XMX_Button_onTouchBegan XMX_Button_onTouchMoved XMX_Button_onTouchEnded ����������Ӧ������
//��Ҫʹ��ť��ϴ��ش��ݣ��ж� XMX_Button_onTouchBegan �ķ���ֵ��Ϊtrue��δ���ص���Ϊfalse�򴥿ص�
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	typedef bool(*Method)();
	class Button_Node : public Node //��ť�ڵ�
	{
	public:
		Sprite* button; //��ť��ʾ��Sprite
		Rect rect; //��Ӧ���ص�����
		Method onPress; //����ť����ʱ�����ĺ���
		Method onRelease; //����ť�ɿ�ʱ�����ĺ���
		bool buttonFlag; //��ť�Ƿ��ѱ���ʼ��
		bool touchFlag; //��ť�Ƿ񱻰���
		bool allowFlag; //��ť�Ƿ�����ʹ��
		bool needResponseFlag; //�Ƿ���Ҫ��Ӧ
		std::map<int, int> data; //Ԥ�����ݿռ�

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
		bool addButton(int id, Sprite* button, float size, int x, int y, float anchorX = 0.5, float anchorY = 0.5, Method press = NULL, Method release = NULL); //ͨ��Sprite��Ӱ�ť
		bool addButton(int id, Rect rect, Method press = NULL, Method release = NULL); //ͨ��������Ӱ�ť
		bool changeButton(int id, Sprite* button, float size, int x, int y, float anchorX = 0.5, float anchorY = 0.5); //ͨ��Sprite���İ�ťͼ��
		bool removeButton(int id); //�Ƴ���ť
		bool hiddenButton(int id); //���ذ�ť
		bool showButton(int id); //��ʾ��ť
		void setData(int id, int index, int data); //���/�޸�����
		int getData(int id, int index); //�������
		void setVibratorTime(int time); //������ʱ��
		void allow(int id); //����Ϊ����ʹ��
		void forbidden(int id); //����Ϊ��ֹʹ��
		bool isNeedResponse(int id); //�ж��Ƿ���Ҫ��Ӧ
		void responsed(int id); //��Ӧ��ť
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
