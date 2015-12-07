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
	OnShiFa(target);
	switch (data->ID)
	{
	case 101:
		OnQiangLiYiJi(data, target);
		break;
	}

}
void CSkillManager::OnQiangLiYiJi(CSkillData *skill, CSolider*target)
{
	CBuffData *data = new CBuffData();
	data->AttackType = 1;
	data->AttackRange = 0;
	data->ContinueTime = 0;
	data->Damage = target->Data_->Attack*skill->HurtCf;
	data->AttackInveralCf = 0;
	data->From = target;
	data->InveralTime = 0;
	data->NextBuff = NULL;
	data->ResourceFrameCount = skill->ResourceFrameCount;
	data->ResourceName = skill->ResourceName;
	data->SpeedCf = 0;
	data->Target = target->AttackTarget;
	CBuff*buff = new CBuff(data);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
}
void CSkillManager::OnShiFa(CSolider* target)
{
	CBuffData *bufdata = new CBuffData();
	bufdata->ResourceName = "SF";
	bufdata->Target = target;
	bufdata->ContinueTime =0;
	bufdata->AttackType = 1;
	bufdata->ResourceFrameCount = 4;
	bufdata->NextBuff = NULL;
	CBuff * buff = new CBuff(bufdata);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
}
