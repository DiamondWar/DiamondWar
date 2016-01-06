#pragma once
#ifndef _CBULLET_H_
#define  _CBULLET_H_

#include "cocos2d.h"
#include "Solider.h"
#include "AttackData.h"
class CBullet :
	public CBattleObject
{
public:

	CBullet(CAttackData* data, int x, int y, CBuffData* damage, CBaseBoss* target, int rank, int type);
	~CBullet();
	virtual void Update();
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
	bool  CheckIsAtTarget();
	CAttackData* Data_;
	CBuffData* BuffData;
	int Ranks_;
	int Damage;
private: 
	float iSpeed_;
	CBaseBoss*  AtTarget_;
	cocos2d::Node* TargetNode;
	int FrameCount;

};

#endif