#pragma once

/****************************************************************************
//���� setJumpButton ������Ӧ���ص�����
//���� setJumpSpeed ������Ծ�ٶ�
//���� setSensitivity ����������
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
	class JumpGesture : public virtual Layer
	{
	private:
		Point sourcePoint; //��ʼ����λ��
		int sensitivity; //������
		int vibratorTime; //��ʱ��
		float jumpSpeed; //��Ծ�ٶ�
		float speedY; //�����ٶ�
		float gravity; //��ǰ������С
		float lowGravity; //������״̬������С
		float highGravity; //������״̬������С
		Rect jumpRect; //��Ӧ���ص�����
		bool jumpButtonFlag; //�Ƿ���������Ծ��ť
		bool touchFlag; //�Ƿ��ѱ�����
		bool allowJumpFlag; //�Ƿ�������Ծ
		bool allowJumpTwiceFlag; //�Ƿ����������
		bool jumpOnceFlag; //�Ƿ�����Ծһ��
		bool jumpTwiceFlag; //�Ƿ�����Ծ����
		bool highGravityFlag; //�Ƿ�Ϊ������ģʽ
		bool jumpSpeedFlag; //�Ƿ���������Ծ�ٶ�
		bool sensitivityFlag; //�Ƿ�������������
		bool touchJumpFlag; //�Ƿ񴥿��Ѵ�����Ծ
		bool gravityEffectFlag; //�Ƿ��ܵ�����Ӱ��

		bool checkControler(); //�����Ծ��ť�Ƿ��ѱ��ɹ�����
		void setHighGravity();  //����Ϊ������ģʽ����Ծ�����׶β��ٴ��ص�������
		void setLowGravity();  //����Ϊ������ģʽ��δ��Ծ����Ծ�����׶ΰ�ס��Ծ��ť����Ծ����׶ε�������

	public:
		JumpGesture(void);
		void setJumpButton(Rect jumpRect); //������Ӧ���ص�����
		void setJumpSpeed(float jumpSpeed); //������Ծ�ٶ�
		void setSensitivity(int sensitivity); //����������
		void setVibratorTime(int time); //������ʱ��
		void allowJump(); //����Ϊ������Ծ
		void notAllowJump();  //����Ϊ��������Ծ���������䣩
		void forbidden();  //����Ϊ��ֹ��Ծ�����岻��������Ӱ�죬�����ٶ���ʧ��
		void setGravity(float gravity);  //�����������͡���������ͬ��
		void setGravity(float lowGravity, float highGravity); //�����������ֱ����õ͡���������
		float getSpeedY();  //��������ٶ�
		void resumeJump(); //�ָ�Ϊδ��Ծ״̬�����ʱ���ã�
		void gravityEffect(); //ÿ֡ʹ������������Ӱ�죨Ӧ��������update�����У�
		bool onTouchBegan(Touch *touch, Event *unused_event);
		void onTouchMoved(Touch *touch, Event *unused_event);
		void onTouchEnded(Touch *touch, Event *unused_event);
	};
}
