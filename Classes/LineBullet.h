#pragma once
#include "Bullet.h"

class CLineBullet:public CBattleObject
{
public:
	CLineBullet(CAttackData* data, int x, int y, CBuffData* damage, CBaseBoss* target, int rank, int type);
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
	float iSpeed_;
	float LineLength = 0;
	float Angle_;
	CBaseBoss* AtTarget_ = nullptr;
	CBaseBoss*  LastTarget_ = nullptr;
	cocos2d::Node* TargetNode;
	int FrameCount;
	bool IsGetMaxLength = false;
};

