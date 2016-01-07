#pragma once
#ifndef _CSPELLMANAGER_H_
#define  _CSPELLMANAGER_H_
#include "SpellData.h"
#include "Solider.h"
#include "cocos2d.h"
class CSpellManager
{
public:
	CSpellManager();
	~CSpellManager();
	static CSpellManager* GetInstance();
	void ChoseSpell(CSpellData*data);
private:
	static CSpellManager* Instance_;

	void OnAttackByType1(CSpellData* attack);
};

#endif 