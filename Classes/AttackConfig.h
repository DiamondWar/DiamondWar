#pragma once
#include "cocos2d.h"
#include "AttackData.h"
 class CAttackConfig
{
public:
	CAttackConfig();
	~CAttackConfig();

	void LoadText();
	static CAttackConfig* GetInstance();
	CAttackData* GetItemById(int id);
	cocos2d::Vector<CAttackData*> DataList_;
private:
	std::string  StressText = "Attack_Config.txt";
	static CAttackConfig* Instance_;
};

