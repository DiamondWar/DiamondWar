#pragma once
#ifndef _CBUFFDATA_H_
#define _CBUFFDATA_H_
#include "cocos2d.h"
#include "ESystemEnum.h"
#include "Solider.h"
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
	int attackPoint = 0;
	int init_x = 0;
	int init_y = 0;
	//�����˺�ֵ
	float AttackCf = 0;
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
	CBuffData* NextBuff = nullptr;
	//��ǰĿ��
	CSolider* Target = nullptr;
	CSolider* From  = nullptr;
	std::string ResourceName="";
	int ResourceFrameCount = 0;
	CBuffData(); 
	~CBuffData();
};
#endif

