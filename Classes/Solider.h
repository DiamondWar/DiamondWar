#pragma once
#ifndef _CSOLIDER_H_
#define _CSOLIDER_H_
#include "BattleObject.h"
#include "SoliderData.h"
#include "SkillData.h"
#include "BaseBoss.h"
class CSolider :public CBaseBoss
{
public:
	CSolider(int id, int type, int rank);
	~CSolider();

	//¹¥»÷·¶Î§
	float AttakRange = 300;
	//¹¥»÷¼ä¸ô
	int AttakInveral = 5;
	virtual void OnResourceLoadComplete();
	virtual void OnAttackActionComplete() ;
	virtual void OnHurtActionComplete();
	virtual void OnSkillActionComplete();
	virtual void Update();

	virtual void OnHurt();
	virtual void OnIdle();
	virtual void OnRun();
	virtual void OnAttack();
	virtual void OnSkill();
	//¼ì²â·¶Î§ÄÚµÄµÐÈË
	bool CheckEnemyInRange();
	//¼ì²â·¶Î§ÄÚµÄ¶ÓÓÑ
	void CheckFriendInRange();
	//ÊÜÉËº¦
	void GetDamage(int damage);
	//ÏÔÊ¾ÊÜÉË
	void ShowHurt();
	CSolider* AttackTarget = nullptr;
	CSoliderData* Data_;
	CSkillData* AttackData_;
	CSkillData* SKillData_;
	//ÒÆ¶¯ËÙ¶È
	int MoveSpeed = 0 ;

private: 
	ESoliderOpreate OpreateType =ESoliderOpreate_Idle;
	//ËÙ¶È
	int speed_x = 1;
	int spped_y = 0;
	//ÉÏ´Î¹¥»÷µÄÊ±¼ä
	long LastAttackTime = 0;
	long NowTime = 0;
	int AttackDamage;
	bool isShowHurt = false;
	long lastShowHurtTime = 0;
	//¹¥»÷´ÎÊý
	int AttackNum=0;
	void CheckAttackOrSkill();
};

#endif 

