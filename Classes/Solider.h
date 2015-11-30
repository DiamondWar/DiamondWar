#pragma once
#ifndef _CSOLIDER_H_
#define _CSOLIDER_H_
#include "BattleObject.h"
#include "SoliderData.h"
#include "SkillData.h"
class CSolider :public CBattleObject
{
public:
	CSolider(int id, int type, int rank);
	~CSolider();
	//队伍id
	int Ranks = 0;
	//攻击范围
	float AttakRange = 300;
	//攻击间隔
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
	//检测范围内的敌人
	bool CheckEnemyInRange();
	//检测范围内的队友
	void CheckFriendInRange();
	//受伤害
	void GetDamage(int damage);
	//显示受伤
	void ShowHurt();
	CSolider* AttackTarget = nullptr;
	CSoliderData* Data_;
	CSkillData* AttackData_;
	CSkillData* SKillData_;
	//移动速度
	int MoveSpeed = 0 ;
	//当前血量
	int CurHp;
	//总血量
	int MaxHp;

private: 
	ESoliderOpreate OpreateType =ESoliderOpreate_Idle;
	//速度
	int speed_x = 1;
	int spped_y = 0;
	//上次攻击的时间
	long LastAttackTime = 0;
	long NowTime = 0;
	int AttackDamage;
	bool isShowHurt = false;
	long lastShowHurtTime = 0;
};

#endif 

