#pragma once
#include "Bullet.h"

class CLineBullet:public CBattleObject
{
public:
	CLineBullet(CAttackData* data, int x, int y, CBuffData* damage, CSolider* target, int rank, int type);
	~CLineBullet();
	virtual void Update();
	virtual void OnResourceLoadComplete();
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete();
	virtual void OnSkillActionComplete();
	bool  CheckIsAtTarget();
	CAttackData* Data_;
	CBuffData* BuffData;
	int Ranks_;
	int Damage;
private: 
	int iSpeed_;
	int LineLength = 0;
	CSolider*  AtTarget_;
	cocos2d::Node* TargetNode;
	int FrameCount;
};

