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

	void GetDamage(int damage, int type);
	void GetMoveSpeedCf(float cf);
	void GetAttackSpeedCf(float cf);
	void GetAttackRangeCf(float cf);
	void GetAttackCf(float cf);
	void GetBuff(CBuffData* data);
	//��ʾ����
	void ShowHurt();
	CSolider* AttackTarget = nullptr;
	CSoliderData* Data_;
	CAttackData* AttackData_;
	CSkillData* SKillData_;
	cocos2d::Node* BasePoint_;
	cocos2d::Node* CenterPoint_;
	cocos2d::Node* LeftPoint_;
	cocos2d::Node* RightPoint_;
	cocos2d::Node* UpPoint_;
	cocos2d::Node* BulletPoint_;
	cocos2d::Vec2 BulletPos_;
	int AttackDamage;
	float AttakRange = 300;
private:
	ESoliderOpreate OpreateType = ESoliderOpreate_Idle;
	//�ϴι�����ʱ��
	long LastAttackTime = 0;
	long NowTime = 0;
	
	bool isShowHurt = false;
	long lastShowHurtTime = 0;
	//��������
	int AttackNum = 0;
	int init_AttackInveral = 0;
	int Init_MoveSpeed = 0;
	int Init_AttackRange = 0;
	int CurBlood = 0;
	int MaxBlood = 0;
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

	void CheckAttackOrSkill();
	cocos2d::Node* CSolider::getBulletPoint(cocos2d::Node* node, std::string name);
	cocos2d::Vec2 CSolider::GetBulletpos(cocos2d::Node*node, cocos2d::Vec2 pos);


};

#endif 

