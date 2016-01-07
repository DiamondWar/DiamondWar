#pragma once
#include "Bullet.h"
class CSpellLiuXingBullet:public CBattleObject
{
public:
	CSpellLiuXingBullet(CAttackData* data, int x, int y, CBuffData* damage,int length, int rank, int type);
	~CSpellLiuXingBullet();
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
	float iSpeed_;
	int Target_x;
	int Target_y;
	cocos2d::Node* TargetNode;
	int FrameCount;
};

