#pragma once
#include "Solider.h"
#include "cocos2d.h"
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
	
	int init_x = 0;
	int init_y = 0;
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
	CBuffData* NextBuff= NULL;
	//当前目标
	CSolider* Target = NULL;
	CSolider* From = NULL;
	std::string ResourceName="";
	int ResourceFrameCount = 0;
	CBuffData(); 
	~CBuffData();
};

