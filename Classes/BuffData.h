#pragma once
#include "Solider.h"
#include "cocos2d.h"
class CBuffData
{
public:

	//攻击方式1.单体2.范围,3固定点范围4 跟踪型范围
	int AttackType;
	//范围
	float AttackRange;
	//受到的伤害值
	int Damage;
	//减速系数
	float SpeedCf;
	int init_x;
	int init_y;
	//减少攻速
	float AttackInveralCf;
	//持续时间
	float ContinueTime;
	//间隔时间
	float InveralTime;
	//下一个buff;
	CBuffData* NextBuff;
	//当前目标
	CSolider* Target;
	CSolider* From;
	std::string ResourceName;
};

