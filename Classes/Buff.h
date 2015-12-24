#pragma once
#ifndef _CBUFF_H_
#define  _CBUFF_H_

#include "BattleObject.h"
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
	long long  StartTime;
	long long LastTime;
	long  long NowTime;
	void GetResultHurt();
};
#endif 


