#pragma once
#ifndef _CSOLIDER_H_
#define _CSOLIDER_H_
#include "BattleObject.h"
#include "SoliderData.h"
#include "SkillData.h"
#include "BaseBoss.h"
#include "AttackData.h"
class CBuffData;
class CSolider :public CBaseBoss
{
public:
	CSolider();
	CSolider(int id, int type, int rank, float level);
	~CSolider();


	virtual void OnResourceLoadComplete();
	virtual void OnAttackActionComplete();
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

	virtual void GetDamage(int damage, int type);
	virtual void GetMoveSpeedCf(float cf);
	virtual void GetAttackSpeedCf(float cf);
	virtual void GetAttackRangeCf(float cf);
	virtual void GetAttackCf(float cf);
	virtual void GetBuff(CBuffData* data);
	//显示受伤
	void ShowHurt();
	//得到子弹位置
	float GetBulletPointToBulletY();
	float GetBulletPointToBulletX();
	virtual cocos2d::Vec2 UpdateBulletPosition();
	CBaseBoss* AttackTarget = nullptr;
	CSoliderData* Data_;
	CAttackData* AttackData_;
	CSkillData* SKillData_;
	
	int AttackDamage;
	float AttakRange = 300;
private:
	ESoliderOpreate OpreateType = ESoliderOpreate_Idle;
	//上次攻击的时间
	long  long LastAttackTime = 0;
	long  long NowTime = 0;
	
	bool isShowHurt = false;
	long lastShowHurtTime = 0;
	//攻击次数
	int AttackNum = 0;
	float init_AttackInveral = 0;
	int Init_MoveSpeed = 0;
	int Init_AttackRange = 0;
	
	//攻击范围//攻击范围系数
	float AttackRangeCf = 0;
	//攻击力削弱
	float AttackCf = 0;
	//攻击间隔
	float AttakInveralCf = 0;
	int AttakInveral = 5;
	//移动速度
	float MoveSpeedCf = 0;
	int MoveSpeed = 0;

	//技能时间
	int MaxSkillFrame = 0;
	bool CheckAttackOrSkill();
	cocos2d::Node* getBulletPoint(cocos2d::Node* node, std::string name);


};

#endif 

