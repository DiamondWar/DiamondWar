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
	switch (data->BulletType)
	{
	case 1:
		OnAttackByType1(target, data);
		break;
	case 2:
		OnAttackByType2(target, data);
		break;
	case 3:
		OnAttackByType3(target, data);
		break;
	case 4:
		OnAttackByType4(target, data);
		break;
	case 5:
		OnAttackByType5(target, data);
		break;
	case 6:
		OnAttackByType6(target, data);
		break;
	case 7:
		OnAttackByType7(target,data);
		break;
	}

}
Vector<CSolider*>CSkillManager::GetList(CSolider* solider , CSkillData* attack)
{
	Vector<CSolider*>list;
	if (attack->TargetRank == 2)
	{
		if (attack->TargetType == 3)
		{
			list = CBattleObjectManager::GetInstance()->GetFriendListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 2)
		{
			list = CBattleObjectManager::GetInstance()->GetFeiXingFriendListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 1)
		{
			list = CBattleObjectManager::GetInstance()->GetLuDiFriendListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
	}
	else if (attack->TargetRank == 3)
	{
			list = CBattleObjectManager::GetInstance()->GetSoliderListByRange( attack->TargetType,solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
	}
	else if (attack->TargetRank == 1)
	{
		if (attack->TargetType == 3)
		{
			list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 2)
		{
			list = CBattleObjectManager::GetInstance()->GetFeiXingEnemyListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 1)
		{
			list = CBattleObjectManager::GetInstance()->GetLuDiEnemyListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
	}
	return list;
}
void CSkillManager::OnAttackByType1(CSolider* solider, CSkillData* attack)
{
	CBuffData*buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->Damage = attack->HurtCf*solider->AttackDamage;
	buffdata->ContinueTime = 0;
	buffdata->attackPoint = attack->AttackPoint;
	buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
	buffdata->ResourceName = attack->ResourceName2;
	buffdata->From = solider;
	buffdata->Target = solider->AttackTarget;
	CBuff * buff = new CBuff(buffdata);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	
}
void CSkillManager::OnAttackByType2(CSolider* solider, CSkillData* attack)
{
	
}
void CSkillManager::OnAttackByType3(CSolider* solider, CSkillData* attack)
{
	Vector<CSolider*>list = GetList(solider,attack);
	for (CSolider* sol : list)
	{
		CBuffData* data = new CBuffData();
		data->AttackType = 1;
		data->attackPoint = attack->AttackPoint;
		if (attack->EffectId == 1)
		{
			data->Damage = attack->EffectValue[0];
		}
		 if (attack->EffectId == 2)
		{
			 data->ContinueTime = attack->EffectValue[0];
			 data->SpeedCf = attack->EffectValue[1];
			 data->AttackInveralCf = attack->EffectValue[2];
		}
		else if (attack->EffectId == 3)
		{
			data->ContinueTime = attack->EffectValue[0];
			data->AttackCf = attack->EffectValue[1];
		}

		 data->attackPoint = attack->AttackPoint;
		 data->From = solider;
		 data->Target = sol;
		 CBuff * buff = new CBuff(data);
		 CBattleObjectManager::GetInstance()->AddBuffObject(buff);
		 if (attack->ResourceFrameCount2 != 0)
		 {
			 CBuffData*buffdata = new CBuffData();
			 buffdata->ContinueTime = 0;
			 buffdata->attackPoint = 1;
			 buffdata->From = solider;
			 buffdata->Target = sol;
			 buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
			 buffdata->ResourceName = attack->ResourceName2;
			 CBuff * buff = new CBuff(buffdata);
			 CBattleObjectManager::GetInstance()->AddBuffObject(buff);
		 }
	}
}
void CSkillManager::OnAttackByType4(CSolider* solider, CSkillData* data)
{

}
void CSkillManager::OnAttackByType5(CSolider* solider, CSkillData* data)
{

}
void CSkillManager::OnAttackByType6(CSolider* solider, CSkillData* data)
{

}
void CSkillManager::OnAttackByType7(CSolider* solider, CSkillData* data)
{

}