#pragma once
#ifndef _CBUFFDATA_H_
#define _CBUFFDATA_H_
#include "cocos2d.h"
#include "ESystemEnum.h"
#include "Solider.h"
class CBuffData
{
public:

	//攻击方式1.单体2.范围,3固定点范围4 跟踪型范围
	int AttackType = 1;
	EBuffType BuffType = E_Buff_None;
	//范围
	float AttackRange = 0;
	//受到的伤害值
	int Damage= 0;
	int attackPoint = 0;
	int init_x = 0;
	int init_y = 0;
	//减少伤害值
	float AttackCf = 0;
	//减少攻速
	float AttackInveralCf = 0;
	//减速系数
	float SpeedCf = 0;
	//减少范围
	float AttackRangeCf = 0;
	//持续时间
	float ContinueTime = 0;
	//间隔时间
	float InveralTime = 0;
	//下一个buff;
	CBuffData* NextBuff = nullptr;
	//当前目标
	CSolider* Target = nullptr;
	CSolider* From  = nullptr;
	std::string ResourceName="";
	int ResourceFrameCount = 0;
	CBuffData(); 
	~CBuffData();
};
#endif

