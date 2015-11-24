#pragma once
#include "cocos2d.h"
class CSoliderData
{
public:
	CSoliderData();
	~CSoliderData();

	int ID;
	std::string Name;
	int Type;
	int NeedStar;
	int AttackId;
	int SkillId;
	int Attack;
	int Blood;
	int MoveSpeed;
	int AttackRange;
	std::string Desc;
};

