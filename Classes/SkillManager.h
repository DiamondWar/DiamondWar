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
	void OnQiangLiYiJi(CSkillData *data,CSolider*target);
	void OnZhaoHuanShanDian(CSkillData *skill, CSolider*target);
	void OnHanBingLingYu(CSkillData *skill, CSolider*target);
	void OnShouHuZhiGuang(CSkillData *skill, CSolider*target);
	void OnQianNengJiFa(CSkillData *skill, CSolider*target);
	void OnQiangLiHuDun(CSkillData *skill, CSolider*target);
};

#endif 