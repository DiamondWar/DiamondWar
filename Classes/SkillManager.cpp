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
	case 201:
		OnZhaoHuanShanDian(data, target);
		break;
	case 401:
		OnHanBingLingYu(data, target);
		break;
	case 501:
		OnQiangLiHuDun(data, target);
		break;
	case 601:
		OnShouHuZhiGuang(data, target);
		break;
	case 602:
		OnQianNengJiFa(data, target);
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
	if (skill->BulletType == 1)
	{
		CBuff * buff = new CBuff(data);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
	else
	{
		CBullet* buttlet = new CBullet(target->AttackData_, target->Obj->getPosition().x, target->Obj->getPosition().y, data, target->AttackTarget, target->Ranks, 2);
		target->Obj->getParent()->addChild(buttlet->Obj);
		CBattleObjectManager::GetInstance()->AddBulletObject(buttlet);
	}
	
}
void CSkillManager::OnZhaoHuanShanDian(CSkillData *skill, CSolider*target)
{
	Vector<CSolider*> list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(target->Ranks, target->AttakRange, target->RangeR_, target->Obj->getPosition().x, target->Obj->getPosition().y);
	for (CSolider* key : list)
	{
		CBuffData *data = new CBuffData();
		data->BuffType = E_Buff_LowBlood;
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
		data->Target = key;
		CBuff * buff = new CBuff(data);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
}
void CSkillManager::OnHanBingLingYu(CSkillData *skill, CSolider*target)
{
	Vector<CSolider*> list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(target->Ranks, target->AttakRange, target->RangeR_, target->Obj->getPosition().x, target->Obj->getPosition().y);
	for (CSolider* key : list)
	{
		CBuffData *data = new CBuffData();
		data->AttackType = 1;
		data->BuffType = E_Buff_NoAction;
		data->AttackRange = 0;
		data->ContinueTime = skill->EffectValue[0];
		data->Damage = target->Data_->Attack*skill->HurtCf;
		data->AttackInveralCf = data->ContinueTime+1;
		data->From = target;
		data->InveralTime = 0;
		data->NextBuff = NULL;
		data->ResourceFrameCount = skill->ResourceFrameCount;
		data->ResourceName = skill->ResourceName;

		data->SpeedCf = -1;
		data->Target = key;
		CBuff * buff = new CBuff(data);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
}
void CSkillManager::OnShouHuZhiGuang(CSkillData* skill, CSolider*target)
{
	Vector<CSolider*> list = CBattleObjectManager::GetInstance()->GetFriendListByRange(target->Ranks, target->AttakRange, target->RangeR_, target->Obj->getPosition().x, target->Obj->getPosition().y);
	for (CSolider* key : list)
	{
		CBuffData *data = new CBuffData();
		data->AttackType = 1;
		data->BuffType = E_Buff_NoHurt;
		data->AttackRange = 0;
		data->ContinueTime = skill->EffectValue[0];
		data->Damage = 0;
		data->AttackCf = 1;
		data->AttackInveralCf =0;
		data->From = target;
		data->InveralTime = 0;
		data->NextBuff = NULL;
		data->ResourceFrameCount = skill->ResourceFrameCount;
		data->ResourceName = skill->ResourceName;
		data->SpeedCf = 0;
		data->Target = key;
		CBuff * buff = new CBuff(data);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
}
void CSkillManager::OnQianNengJiFa(CSkillData *skill, CSolider*target)
{
	Vector<CSolider*> list = CBattleObjectManager::GetInstance()->GetFriendListByRange(target->Ranks, target->AttakRange, target->RangeR_, target->Obj->getPosition().x, target->Obj->getPosition().y);
	for (CSolider* key : list)
	{
		CBuffData *data = new CBuffData();
		data->AttackType = 1;
		data->BuffType = E_Buff_HighSpeed;
		data->AttackRange = 0;
		data->ContinueTime = skill->EffectValue[0];
		data->Damage = 0;
		data->AttackCf = 0;
		data->AttackInveralCf = skill->EffectValue[2];
		data->From = target;
		data->InveralTime = 0;
		data->NextBuff = NULL;
		data->ResourceFrameCount = skill->ResourceFrameCount;
		data->ResourceName = skill->ResourceName;
		data->SpeedCf = skill->EffectValue[1];
		data->Target = key;
		CBuff * buff = new CBuff(data);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
}
void CSkillManager::OnQiangLiHuDun(CSkillData *skill, CSolider*target)
{
	CBuffData *data = new CBuffData();
	data->AttackType = 1;
	data->BuffType = E_Buff_HighSpeed;
	data->AttackRange = 0;
	data->ContinueTime = skill->EffectValue[0];
	data->Damage = 0;
	data->AttackCf = 1;
	data->AttackInveralCf =0;
	data->From = target;
	data->InveralTime = 0;
	data->NextBuff = NULL;
	data->ResourceFrameCount = skill->ResourceFrameCount;
	data->ResourceName = skill->ResourceName;
	data->SpeedCf = 0;
	data->Target = target;
	CBuff * buff = new CBuff(data);
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
