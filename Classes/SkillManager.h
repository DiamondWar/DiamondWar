#pragma once
#ifndef _CSKILLMANAGER_H_
#define  _CSKILLMANAGER_H_
#include "SkillData.h"
#include "Solider.h"
#include "cocos2d.h"
class CSkillManager
{
public:
	CSkillManager();
	~CSkillManager();
	void OnShiFa(CSolider* target);
	static CSkillManager* GetInstance();
	void ChoseSkill(CSkillData*data, CSolider* target);
private:
	static CSkillManager* Instance_;


	void OnAttackByType1(CSolider* solider, CSkillData* attack);
	void OnAttackByType2(CSolider* solider, CSkillData* data);
	void OnAttackByType3(CSolider* solider, CSkillData* data);
	void OnAttackByType4(CSolider* solider, CSkillData* data);
	void OnAttackByType5(CSolider* solider, CSkillData* data);
	void OnAttackByType6(CSolider* solider, CSkillData* data);
	void OnAttackByType7(CSolider* solider, CSkillData* data);
	cocos2d::Vector<CSolider*> GetList(CSolider* solider, CSkillData* attack);
};

#endif 