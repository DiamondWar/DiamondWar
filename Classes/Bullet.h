#pragma once
#include "cocos2d.h"
#include "Solider.h"
#include "SkillData.h"
#include "BuffData.h"
class CBullet :
	public CBattleObject
{
public:

	CBullet(CSkillData* data, int x, int y, CBuffData* damage, CSolider* target, int rank, int type);
	~CBullet();
	virtual void Update();
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
	bool  CheckIsAtTarget();
	CSkillData* Data_;
	CBuffData* BuffData;
	int Ranks_;
	int Damage;
private: 
	int iSpeed_;
	CSolider*  AtTarget_;

};

