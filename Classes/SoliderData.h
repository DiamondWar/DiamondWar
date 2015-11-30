#pragma once
#include "cocos2d.h"
class CSoliderData :public cocos2d::Node
{
public:
	CSoliderData();
	~CSoliderData();

	int ID;
	std::string Name;
	int Type;
	int RangeR;
	int NeedStar;
	int AttackId;
	int SkillId;
	int Attack;
	int Blood;
	float MoveSpeed;
	float AttackRange;
	float AttackInterval;
	std::string Desc;
	std::string ResourceName;
};

