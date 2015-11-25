#pragma once
#include "cocos2d.h"
#include "SkillData.h"
class CSkillConfig
{
public:
	CSkillConfig();
	~CSkillConfig();
	void LoadText();
	static CSkillConfig* GetInstance();
	CSkillData* GetItemById(int id);
private:
	std::string  StressText = "Skill_Config.txt";
	static CSkillConfig* Instance_;
	cocos2d::Vector<CSkillData*> DataList_;
};

