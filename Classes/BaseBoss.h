#pragma once
#include "cocos2d.h"
#include "BattleObject.h"
class CBaseBoss :public CBattleObject
{
public:
	CBaseBoss();
	CBaseBoss(int rank);
	~CBaseBoss();
	//����id
	int Ranks;
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
	//��ǰѪ��
	int CurHp;
	//��Ѫ��
	int MaxHp;
};

