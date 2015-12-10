#pragma once
#include "Solider.h"
#include "cocos2d.h"
class CBuffData
{
public:

	//������ʽ1.����2.��Χ,3�̶��㷶Χ4 �����ͷ�Χ
	int AttackType = 1;
	EBuffType BuffType = E_Buff_None;
	//��Χ
	float AttackRange = 0;
	//�ܵ����˺�ֵ
	int Damage= 0;
	
	int init_x = 0;
	int init_y = 0;
	//���ٹ���
	float AttackInveralCf = 0;
	//����ϵ��
	float SpeedCf = 0;
	//���ٷ�Χ
	float AttackRangeCf = 0;
	//����ʱ��
	float ContinueTime = 0;
	//���ʱ��
	float InveralTime = 0;
	//��һ��buff;
	CBuffData* NextBuff= NULL;
	//��ǰĿ��
	CSolider* Target = NULL;
	CSolider* From = NULL;
	std::string ResourceName="";
	int ResourceFrameCount = 0;
	CBuffData(); 
	~CBuffData();
};

