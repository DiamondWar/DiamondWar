#pragma once
#ifndef _CSKILLCONFIG_H_
#define _CSKILLCONFIG_H_
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
	std::string  StressText = "SkillConfig.txt";
	static CSkillConfig* Instance_;
	cocos2d::Vector<CSkillData*> DataList_;
};
#endif 
