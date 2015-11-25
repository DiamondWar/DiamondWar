#pragma once
#ifndef _CSOLIDER_H_
#define _CSOLIDER_H_
#include "BattleObject.h"
#include "SoliderData.h"
class CSolider :public CBattleObject
{
public:
	CSolider(int id, std::string name, int x, int y, int type, int rank);
	~CSolider();
	//¶ÓÎéid
	int Ranks = 0;
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
	CSolider* AttackTarget = nullptr;
	CSoliderData* Data_;
	int MoveSpeed = 0 ;
private: 
	ESoliderOpreate OpreateType =ESoliderOpreate_Idle;
	//ËÙ¶È
	int speed_x = 1;
	int spped_y = 0;
	//ÉÏ´Î¹¥»÷µÄÊ±¼ä
	long LastAttackTime = 0;
	long NowTime = 0;
};

#endif 

