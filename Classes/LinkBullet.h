#pragma once
#include "Bullet.h"
class CLinkBullet :public CBattleObject
{
public:
	CLinkBullet(CAttackData* data, int x, int y, CBuffData* damage, CSolider* target, int rank, int type);
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
	CSolider*  AtTarget_;
	cocos2d::Node* TargetNode;
	int FrameCount;
	float baseWidth;
};

