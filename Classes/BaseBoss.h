#pragma once
#ifndef _CBASEBOSS_H_
#define  _CBASEBOSS_H_
#include "cocos2d.h"
#include "BattleObject.h"
class CBuffData;
class CBaseBoss :public CBattleObject
{
public:
	CBaseBoss();
	CBaseBoss(int rank);
	~CBaseBoss();
	//∂”ŒÈid
	int Ranks;
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
	virtual void GetDamage(int damage, int type);
	virtual void GetMoveSpeedCf(float cf);
	virtual void GetAttackSpeedCf(float cf);
	virtual void GetAttackRangeCf(float cf);
	virtual void GetAttackCf(float cf);
	virtual void GetBuff(CBuffData* data);
	virtual void Update();
	virtual void OnHurt();
	virtual void OnIdle();
	virtual void OnRun();
	virtual void OnAttack();
	virtual void OnSkill();
	virtual cocos2d::Vec2 UpdateBulletPosition();
	float CurBlood = 0;
	float MaxBlood = 0;
	cocos2d::Node* BasePoint_;
	cocos2d::Node* CenterPoint_;
	cocos2d::Node* LeftPoint_;
	cocos2d::Node* RightPoint_;
	cocos2d::Node* UpPoint_;
	cocos2d::Node* BulletPoint_;
	cocos2d::Vec2 BulletPos_;
private:
	cocos2d::Sprite* BossSprite_;
};
#endif

