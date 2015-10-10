#pragma once

/****************************************************************************
//���� setJumpButton ������Ծ��ť
//���� hiddenButton ���ذ�ť
//���� showButton ��ʾ��ť
//���� setJumpSpeed ������Ծ�ٶ�
//���� setVibratorTime ������ʱ��
//���� allowJump ����Ϊ������
//���� notAllowJump ����Ϊ��������
//���� forbidden ���ý�ֹ��Ծ�����岻��������Ӱ�죬�����ٶ���ʧ��
//���� setGravity ��������
//���� getSpeedY ����ٶȣ�Ӧ������ update ������ c->setPositionY(c->getPositionY() + getSpeedY())��
//���� resume �ָ�Ϊδ��Ծ״̬�����ʱ���ã�
//���� gravityEffect ÿ֡ʹ������������Ӱ�죨Ӧ�������� update �У�
//�� onTouchBegan onTouchMoved onTouchEnded ����������Ӧ������
****************************************************************************/

#include "XMX_Global.h"

namespace XMX
{
	class JumpButton : public virtual Layer
	{
	private:
		int vibratorTime; //��ʱ��
		float jumpSpeed; //��Ծ�ٶ�
		float speedY; //����˲ʱ�ٶ�
		float gravity; //��ǰ������С
		float lowGravity; //������״̬������С
		float highGravity; //������״̬������С
		Sprite* jumpButton; //��Ծ��ťSprite
		Rect jumpRect; //��Ӧ���ص�����
		bool touchFlag; //�Ƿ��ѱ�����
		bool allowJumpFlag; //�Ƿ�������Ծ
		bool allowJumpTwiceFlag; //�Ƿ����������
		bool jumpOnceFlag; //�Ƿ�����Ծһ��
		bool jumpTwiceFlag; //�Ƿ�����Ծ����
		bool highGravityFlag; //�Ƿ�Ϊ������ģʽ
		bool gravityEffectFlag; //�Ƿ��ܵ�����Ӱ��
		bool jumpButtonFlag; //�Ƿ���������Ծ��ť
		bool jumpSpeedFlag; //�Ƿ���������Ծ�ٶ�

		bool checkControler(); //�����Ծ��ť�Ƿ��ѱ��ɹ�����
		void setHighGravity(); //����Ϊ������ģʽ����Ծ�����׶��ɿ���Ծ��ť��������
		void setLowGravity(); //����Ϊ������ģʽ��δ��Ծ����Ծ�����׶ΰ�ס��Ծ��ť����Ծ����׶ε�������
		void jumpBegan(); //��Ծ��ʼ
		void jumpEnded(); //��Ծ����

	public:
		JumpButton();
		void setJumpButton(Sprite* jumpButton, float size, int x, int y); //ͨ��Sprite������Ծ��ť
		void setJumpButton(Rect jumpRect); //ͨ������������Ծ��ť
		bool hiddenButton(); //���ذ�ť
		bool showButton(); //��ʾ��ť
		void setJumpSpeed(float jumpSpeed); //������Ծ�ٶ�
		void setVibratorTime(int time); //������ʱ��
		void allowJump(); //����Ϊ������Ծ
		void notAllowJump(); //����Ϊ��������Ծ���������䣩
		void forbidden(); //����Ϊ��ֹ��Ծ�����岻��������Ӱ�죬�����ٶ���ʧ��
		void setGravity(float gravity); //�����������͡���������ͬ��
		void setGravity(float lowGravity, float highGravity); //�����������ֱ����õ͡���������
		float getSpeedY(); //��������ٶ�
		void resumeJump(); //�ָ�Ϊδ��Ծ״̬�����ʱ���ã�
		void gravityEffect(); //ÿ֡ʹ������������Ӱ�죨Ӧ��������update�����У�
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
