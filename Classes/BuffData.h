#pragma once
#include "Solider.h"
#include "cocos2d.h"
class CBuffData
{
public:

	//������ʽ1.����2.��Χ,3�̶��㷶Χ4 �����ͷ�Χ
	int AttackType;
	//��Χ
	float AttackRange;
	//�ܵ����˺�ֵ
	int Damage;
	//����ϵ��
	float SpeedCf;
	int init_x;
	int init_y;
	//���ٹ���
	float AttackInveralCf;
	//����ʱ��
	float ContinueTime;
	//���ʱ��
	float InveralTime;
	//��һ��buff;
	CBuffData* NextBuff;
	//��ǰĿ��
	CSolider* Target;
	CSolider* From;
	std::string ResourceName;
};

