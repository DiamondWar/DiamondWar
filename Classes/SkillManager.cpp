#include "SkillManager.h"
#include "BuffData.h"
#include "BattleObjectManager.h"
#include "Buff.h"
USING_NS_CC;

CSkillManager* CSkillManager::Instance_ = nullptr;
CSkillManager::CSkillManager()
{
}
CSkillManager* CSkillManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CSkillManager();
	return Instance_;
}

CSkillManager::~CSkillManager()
{
}

void CSkillManager::ChoseSkill(CSkillData*data, CSolider* target)
{
	CBuffData *bufdata = new CBuffData();
	bufdata->ResourceName = "n000";

	CBuff * buff = new CBuff(bufdata);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
}
void CSkillManager::OnShiFaComplete()
{

}
