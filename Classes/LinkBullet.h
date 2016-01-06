#pragma once
#include "Bullet.h"
class CLinkBullet :public CBattleObject
{
public:
	CLinkBullet(CAttackData* data, int x, int y, CBuffData* damage, CBaseBoss* target, int rank, int type);
	~CLinkBullet();
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
	float AtTargetLength = 0;
	CBaseBoss*  AtTarget_;
	cocos2d::Node* TargetNode;
	int FrameCount= 0;
	float MaxTime = 0;
	int curFrameCount = 0;
	float baseWidth;
};

