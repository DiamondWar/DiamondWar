#pragma once
#include "Solider.h"
#include "cocos2d.h"
class CAttackManager
{
public:
	CAttackManager();
	~CAttackManager();
	static CAttackManager* GetInstance();
	void OnAttack(CSolider* solider, CAttackData* data);
private:
	static CAttackManager* Instance_;
	void OnAttackByType1(CSolider* solider, CAttackData* attack);
	void OnAttackByType2(CSolider* solider, CAttackData* data);
	void OnAttackByType3(CSolider* solider, CAttackData* data);
	void OnAttackByType4(CSolider* solider, CAttackData* data);
	void OnAttackByType5(CSolider* solider, CAttackData* data);
	void OnAttackByType6(CSolider* solider, CAttackData* data);
	void OnAttackByType7(CSolider* solider, CAttackData* data);
	void OnAttackByType8(CSolider* solider, CAttackData* data);
};

