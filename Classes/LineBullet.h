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
	void CheckEnemyInAttackRange();
	CAttackData* Data_;
	CBuffData* BuffData;
	int Ranks_;
	int Damage;
private: 
	int iSpeed_;
	float LineLength = 0;
	float Angle_;
	CSolider* AtTarget_ = nullptr;
	CSolider*  LastTarget_ = nullptr;
	cocos2d::Node* TargetNode;
	int FrameCount;
};

