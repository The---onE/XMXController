#pragma once

/****************************************************************************
//���� setControler ���ÿ�����
//���� setSpeedMax ��������ٶ�
//���� setTouchRect ���ô�������
//���� setVibratorTime ������ʱ��
//���� allowControl ����Ϊ������
//���� notAllowControl() ����Ϊ��������
//���� getSpeed ���˲ʱ�ٶȣ�Ӧ������ update ������ c->setPositionX(c->getPositionX() + getSpeed())��
//�� onTouchBegan onTouchMoved onTouchEnded ����������Ӧ������
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	class ControlBarX : public virtual Layer
	{
	private:
		int vibratorTime; //��ʱ��
		float height; //�������߶�
		float width; //���������
		float speed; //˲ʱ�ٶ�
		float speedMax; //����ٶȣ���������������ʱ��
		Rect touchRect; //��Ӧ���ص����򣨿�ʼ���أ�
		Sprite* bar; //������Sprite
		Sprite* ball; //���ص�Sprite
		bool touchFlag; //�Ƿ��ѿ�ʼ����
		bool allowControlFlag; //�Ƿ�������
		bool touchMaxFlag; //�Ƿ�����������������
		bool leftFlag; //���ص��Ƿ�����ˣ��л����Ҷ�ʱ�𶯣�
		bool rightFlag; //���ص��Ƿ����Ҷˣ��л����Ҷ�ʱ�𶯣�
		bool controlerFlag; //�Ƿ������ÿ�����
		bool speedMaxFlag; //�Ƿ�����������ٶ�
		bool touchRectFlag; //�Ƿ������ô�������

		bool checkControler(); //���������ѱ��ɹ�����

	public:
		ControlBarX();
		bool setControler(Sprite* bar, Sprite* ball, float height, float width); //���ÿ�����
		bool setSpeedMax(float speedMax); //��������ٶ�
		bool setTouchRect(Rect touchRect); //���ô�������
		void setVibratorTime(int time); //������ʱ��
		void allowControl(); //����Ϊ������
		void notAllowControl(); //����Ϊ��������
		float getSpeed(); //���˲ʱ�ٶ�
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
