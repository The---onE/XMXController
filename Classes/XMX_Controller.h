#pragma once

/****************************************************************************
//���� setControler ���ÿ�����
//���� setSpeedMax ��������ٶ�
//���� setTouchRect ���ô�������
//���� setVibratorTime ������ʱ��
//���� set4DirectionMode ����Ϊ�ķ���ģʽ
//���� set8DirectionMode ����Ϊ�˷���ģʽ
//���� allowControl ����Ϊ������
//���� notAllowControl ����Ϊ��������
//���� getSpeedX getSpeedY ���˲ʱ�ٶȣ�Ӧ������ update ������ c->setPositionX(c->getPositionX() + getSpeedX()) c->setPositionY(c->getPositionY() + getSpeedY())��
//�� onTouchBegan onTouchMoved onTouchEnded ����������Ӧ������
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	class Controller : public virtual Layer
	{
	private:
		int vibratorTime; //��ʱ��
		int angleLevel; //���ص����ڽǶ�����
		float rb; //������뾶
		float rs; //���ص�뾶
		float speedX; //����˲ʱ�ٶ�
		float speedY; //����˲ʱ�ٶ�
		float speedMax; //����ٶȣ������������Ե��
		int angle; //���ˮƽ����Ƕ�
		Rect touchRect; //��Ӧ���ص����򣨿�ʼ���أ�
		Sprite* round; //������Sprite
		Sprite* ball; //���ص�Sprite
		bool touchFlag; //�Ƿ��ѿ�ʼ����
		bool allowControlFlag; //�Ƿ�������
		bool touchMaxFlag; //�Ƿ���������Ե
		bool _8directionFlag; //�Ƿ�Ϊ�˷���ģʽ
		bool _4directionFlag; //�Ƿ�Ϊ�ķ���ģʽ
		bool controlerFlag; //�Ƿ����ÿ�����
		bool speedMaxFlag; //�Ƿ�����������ٶ�
		bool touchRectFlag; //�Ƿ������ô�������

		bool checkControler(); //���������Ƿ��ѱ��ɹ�����

	public:
		Controller();
		void setControler(Sprite* round, Sprite* ball, float rb, float rs); //���ÿ�����
		void setSpeedMax(float speedMax); //��������ٶ�
		void setTouchRect(Rect touchRact); //���ô�������
		void setVibratorTime(int time); //������ʱ��
		void set4DirectionMode(bool flag); //����Ϊ�ķ���ģʽ
		void set8DirectionMode(bool flag); //����Ϊ�˷���ģʽ
		void allowControl(); //����Ϊ������
		void notAllowControl(); //����Ϊ��������
		float getSpeedX(); //��ú���˲ʱ�ٶ�
		float getSpeedY(); //�������˲ʱ�ٶ�
		int getAngle(); //������ˮƽ����Ƕ�
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
