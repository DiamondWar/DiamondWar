#pragma once
#ifndef _CSOLIDER_H_
#define _CSOLIDER_H_
#include "BattleObject.h"
class CSolider :public CBattleObject
{
public:
	CSolider(std::string name, int x, int y, int type, int rank,int range);
	~CSolider();
	//����id
	int Ranks = 0;
	//������Χ
	float AttakRange = 300;
	//�������
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
	//��ⷶΧ�ڵĵ���
	bool CheckEnemyInRange();
	//��ⷶΧ�ڵĶ���
	void CheckFriendInRange();
	CSolider* AttackTarget = nullptr;
private: 
	ESoliderOpreate OpreateType =ESoliderOpreate_Idle;
	//�ٶ�
	int speed_x = 1;
	int spped_y = 0;
	//�ϴι�����ʱ��
	long LastAttackTime = 0;
	long NowTime = 0;
};

#endif 

