#include "SpellManager.h"
#include "SpellLiuXingManager.h"
#include "BattleObjectManager.h"
#include "AudioManager.h"
CSpellManager* CSpellManager::Instance_ = nullptr;
CSpellManager::CSpellManager()
{
}
CSpellManager* CSpellManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CSpellManager();
	return Instance_;
}

CSpellManager::~CSpellManager()
{
}
void CSpellManager::ChoseSpell(CSpellData*data)
{
	CAudioManager::GetInstance()->PlayerVoice(data->AttackVoice);
	switch (data->ID)
	{
	case 1:
		OnAttackByType1(data);
		break;
	case 2:
		OnAttackByType1(data);
		break;
	default:
		break;
	}
}
void CSpellManager::OnAttackByType1(CSpellData* attack)
{
	CSpellLiuXingManager* manager = new CSpellLiuXingManager(attack);
	CBattleObjectManager::GetInstance()->AddSpellObject(manager);
}