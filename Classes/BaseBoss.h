#pragma once
#include "cocos2d.h"
#include "BattleObject.h"
class CBaseBoss :public CBattleObject
{
public:
	CBaseBoss();
	CBaseBoss(int rank);
	~CBaseBoss();
	//队伍id
	int Ranks;
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
	//当前血量
	int CurHp;
	//总血量
	int MaxHp;
};

