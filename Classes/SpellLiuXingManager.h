#pragma once
#include "BattleObject.h"
#include "SpellData.h"
#include "BuffData.h"
#include "AttackData.h"
class CSpellLiuXingManager:public CBattleObject
{
public:
	CSpellLiuXingManager(CSpellData* data);
	~CSpellLiuXingManager();
	virtual void Update();
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
private: 
	int Init_Point[5];
	long long NowTime;
	long long LastAttackTime;
	int InvertalTime;
	CBuffData* BuffData_;
	int BulletNum =0;
	int MaxBulletNum =0;
	CAttackData* AttackData_;

	int EffectNum = 0;
	int MaxEffectNum = 100;
	float Hurt = 0;
	long long lastEffectTime;
	CAttackData* EffectData_;
	CBuffData* EffctBuffData_;
};

