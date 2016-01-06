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
	//��ⷶΧ�ڵĵ���
	bool CheckEnemyInRange();
	//��ⷶΧ�ڵĶ���
	void CheckFriendInRange();

	virtual void GetDamage(int damage, int type);
	virtual void GetMoveSpeedCf(float cf);
	virtual void GetAttackSpeedCf(float cf);
	virtual void GetAttackRangeCf(float cf);
	virtual void GetAttackCf(float cf);
	virtual void GetBuff(CBuffData* data);
	//��ʾ����
	void ShowHurt();
	//�õ��ӵ�λ��
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
	//�ϴι�����ʱ��
	long  long LastAttackTime = 0;
	long  long NowTime = 0;
	
	bool isShowHurt = false;
	long lastShowHurtTime = 0;
	//��������
	int AttackNum = 0;
	float init_AttackInveral = 0;
	int Init_MoveSpeed = 0;
	int Init_AttackRange = 0;
	
	//������Χ//������Χϵ��
	float AttackRangeCf = 0;
	//����������
	float AttackCf = 0;
	//�������
	float AttakInveralCf = 0;
	int AttakInveral = 5;
	//�ƶ��ٶ�
	float MoveSpeedCf = 0;
	int MoveSpeed = 0;

	//����ʱ��
	int MaxSkillFrame = 0;
	bool CheckAttackOrSkill();
	cocos2d::Node* getBulletPoint(cocos2d::Node* node, std::string name);


};

#endif 

