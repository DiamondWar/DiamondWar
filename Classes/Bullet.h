#pragma once
#include "cocos2d.h"
#include "Solider.h"
class CBullet :
	public CBattleObject
{
public:
	CBullet(int id, std::string resourename, int x, int y, CSolider* target, int rank, int type);
	~CBullet();
	virtual void Update();
	virtual void OnResourceLoadComplete() ;
	virtual void OnAttackActionComplete();
	virtual void OnHurtActionComplete() ;
	virtual void OnSkillActionComplete();
	bool  CheckIsAtTarget();

	int Ranks_;
private: 
	int iSpeed_;
	CSolider*  AtTarget_;

};

