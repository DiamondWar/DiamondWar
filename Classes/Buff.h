#pragma once
#include "BattleObject.h"
#include "Solider.h"
#include "BuffData.h"
class CBuff:public CBattleObject
{
public:
	CBuff(CBuffData* data);
	~CBuff();

	CBuffData* BuffData;
	virtual void OnResourceLoadComplete();
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete();
	virtual void OnSkillActionComplete();
	virtual void Update();
private:
	long StartTime;
	long LastTime;
	long NowTime;
	void GetResultHurt();
};



