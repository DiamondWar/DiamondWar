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
	//��ⷶΧ�ڵĵ���
	bool CheckEnemyInRange();
	//��ⷶΧ�ڵĶ���
	void CheckFriendInRange();
	
	void GetBuff(CBuffData* damage);
	void GetDamage(int damage, int type = 3);
	void GetMoveSpeedCf(float cf);
	void GetAttackSpeedCf(float cf);
	void GetAttackRangeCf(float cf);
	//��ʾ����
	void ShowHurt();
	CSolider* AttackTarget = nullptr;
	CSoliderData* Data_;
	CSkillData* AttackData_;
	CSkillData* SKillData_;
	

private: 
	ESoliderOpreate OpreateType =ESoliderOpreate_Idle;
	//�ϴι�����ʱ��
	long LastAttackTime = 0;
	long NowTime = 0;
	int AttackDamage;
	bool isShowHurt = false;
	long lastShowHurtTime = 0;
	//��������
	int AttackNum=0;



	//������Χ
	float AttackRangeCf = 0;//������Χϵ��
	float AttakRange = 300;
	//�������
	float AttakInveralCf = 0;
	int AttakInveral = 5;
	//�ƶ��ٶ�
	float MoveSpeedCf = 0;
	int MoveSpeed = 0;

	void CheckAttackOrSkill();

	
	
};

#endif 

