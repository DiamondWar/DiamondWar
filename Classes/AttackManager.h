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
	void CAttackManager::OnAttackByType1(CSolider* solider, CAttackData* attack);
	void CAttackManager::OnAttackByType2(CSolider* solider, CAttackData* data);
	void CAttackManager::OnAttackByType3(CSolider* solider, CAttackData* data);
	void CAttackManager::OnAttackByType4(CSolider* solider, CAttackData* data);
	void CAttackManager::OnAttackByType5(CSolider* solider, CAttackData* data);
	void CAttackManager::OnAttackByType6(CSolider* solider, CAttackData* data);
	void CAttackManager::OnAttackByType7(CSolider* solider, CAttackData* data);
};

