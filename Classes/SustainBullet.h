#pragma once
#include "Bullet.h"
class CSustainBullet :public CBattleObject
{
public:
	CSustainBullet(CAttackData* data, int x, int y, CBuffData* damage, CBaseBoss* target, int rank, int type);
	~CSustainBullet();
	virtual void Update();
	virtual void OnResourceLoadComplete();
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete();
	virtual void OnSkillActionComplete();
	CAttackData* Data_;
	CBuffData* BuffData;
	int Ranks_;
	int Damage;
private:
	
	int BulletNum =0;
	float MaxBulletNum =0;
	int FrameCount = 0;
	int curFrameCount = 0;
	bool IsCanCreateBullet = true;
	cocos2d::Vector<CBullet*> bulletlist;
	CBaseBoss*  AtTarget_;
};

