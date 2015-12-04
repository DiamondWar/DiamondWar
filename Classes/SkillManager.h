#pragma once
#include "SkillData.h"
#include "Solider.h"
#include "cocos2d.h"
class CSkillManager
{
public:
	CSkillManager();
	~CSkillManager();
	void OnShiFaComplete();
	static CSkillManager* GetInstance();
	void ChoseSkill(CSkillData*data, CSolider* target);
private:
	static CSkillManager* Instance_;
	
};

