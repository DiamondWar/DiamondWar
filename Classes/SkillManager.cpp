#include "SkillManager.h"
#include "BuffData.h"
#include "BattleObjectManager.h"
#include "Buff.h"
#include "LineBullet.h"
#include "LinkBullet.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "GameSceneControl.h"
#include "SustainBullet.h"
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
	CAudioManager::GetInstance()->PlayerVoice(data->AttackVoice);
	//OnShiFa(target);
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
		OnAttackByType7(target, data);
		break;
	case 8:
		OnAttackByType8(target, data);
		break;
	}

}
void CSkillManager::OnShiFa(CSolider* target)
{

	CBuffData *bufdata = new CBuffData();
	bufdata->ResourceName = "SF";
	bufdata->Target = target;
	bufdata->ContinueTime = 0;
	bufdata->AttackType = 1;
	bufdata->ResourceFrameCount = 4;
	bufdata->NextBuff = NULL;
	CBuff * buff = new CBuff(bufdata);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
}
Vector<CSolider*>CSkillManager::GetList(CSolider* solider, CSkillData* attack)
{
	Vector<CSolider*>list;
	if (attack->TargetRank == 2)
	{
		if (attack->TargetType == 3)
		{
			list = CBattleObjectManager::GetInstance()->GetFriendListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 2)
		{
			list = CBattleObjectManager::GetInstance()->GetFeiXingFriendListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 1)
		{
			list = CBattleObjectManager::GetInstance()->GetLuDiFriendListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
	}
	else if (attack->TargetRank == 3)
	{
		list = CBattleObjectManager::GetInstance()->GetSoliderListByRange(attack->TargetType, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
			solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
	}
	else if (attack->TargetRank == 1)
	{
		if (attack->TargetType == 3)
		{
			list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 2)
		{
			list = CBattleObjectManager::GetInstance()->GetFeiXingEnemyListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
		else if (attack->TargetType == 1)
		{
			list = CBattleObjectManager::GetInstance()->GetLuDiEnemyListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, solider->RangeR_, solider->Obj->getPosition().x + solider->CenterPoint_->getPosition().x,
				solider->Obj->getPosition().y + solider->CenterPoint_->getPosition().y);
		}
	}
	return list;
}

void CSkillManager::OnAttackByType1(CSolider* solider, CSkillData* attack)
{

	if (attack->BulletValue[0] != 0)
	{
		Vector<CSolider*> list;
		if (attack->TargetRank == 1)
		{
			if (attack->TargetType == 3)
			{
				list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, 0, solider->AttackTarget->Obj->getPosition().x + solider->AttackTarget->CenterPoint_->getPosition().x,
					solider->AttackTarget->Obj->getPosition().y + solider->AttackTarget->CenterPoint_->getPosition().y);
			}
			else if (attack->TargetType == 2)
			{
				list = CBattleObjectManager::GetInstance()->GetFeiXingEnemyListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, 0, solider->AttackTarget->Obj->getPosition().x + solider->AttackTarget->CenterPoint_->getPosition().x,
					solider->AttackTarget->Obj->getPosition().y + solider->AttackTarget->CenterPoint_->getPosition().y);
			}
			else if (attack->TargetType == 1)
			{
				list = CBattleObjectManager::GetInstance()->GetLuDiEnemyListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, 0, solider->AttackTarget->Obj->getPosition().x + solider->AttackTarget->CenterPoint_->getPosition().x,
					solider->AttackTarget->Obj->getPosition().y + solider->AttackTarget->CenterPoint_->getPosition().y);
			}
		}
		else if (attack->TargetRank == 2)
		{
			solider->AttackTarget = solider;
			if (attack->TargetType == 3)
			{
				list = CBattleObjectManager::GetInstance()->GetFriendListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, 0, solider->AttackTarget->Obj->getPosition().x + solider->AttackTarget->CenterPoint_->getPosition().x,
					solider->AttackTarget->Obj->getPosition().y + solider->AttackTarget->CenterPoint_->getPosition().y);
			}
			else if (attack->TargetType == 2)
			{
				list = CBattleObjectManager::GetInstance()->GetFeiXingFriendListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, 0, solider->AttackTarget->Obj->getPosition().x + solider->AttackTarget->CenterPoint_->getPosition().x,
					solider->AttackTarget->Obj->getPosition().y + solider->AttackTarget->CenterPoint_->getPosition().y);
			}
			else if (attack->TargetType == 1)
			{
				list = CBattleObjectManager::GetInstance()->GetLuDiFriendListByRange(solider->Ranks, attack->BulletValue[0] * CCGlobleConfig::COMMON_RANGE_VALUE, 0, solider->AttackTarget->Obj->getPosition().x + solider->AttackTarget->CenterPoint_->getPosition().x,
					solider->AttackTarget->Obj->getPosition().y + solider->AttackTarget->CenterPoint_->getPosition().y);
			}
		}

		for (CSolider* sol : list)
		{
			CBuffData*buffdata = new CBuffData();
			buffdata->AttackType = 1;
			buffdata->Damage = attack->HurtCf*solider->AttackDamage;
			buffdata->ContinueTime = 0;
			buffdata->attackPoint = attack->AttackPoint;

			buffdata->From = solider;
			if (attack->EffectId == 1)
			{
				buffdata->Damage = attack->HurtCf*solider->AttackDamage;
			}
			if (attack->EffectId == 2)
			{
				buffdata->ContinueTime = attack->EffectValue[0];
				buffdata->SpeedCf = attack->EffectValue[1];
				buffdata->AttackInveralCf = attack->EffectValue[2];
				buffdata->ResourceFrameCount = attack->ResourceFrameCount3;
				buffdata->ResourceName = attack->ResourceName3;
			}
			else if (attack->EffectId == 3)
			{
				buffdata->ContinueTime = attack->EffectValue[0];
				buffdata->AttackCf = attack->EffectValue[1];
				buffdata->ResourceFrameCount = attack->ResourceFrameCount3;
				buffdata->ResourceName = attack->ResourceName3;
			}
			else
			{
				buffdata->Damage = attack->HurtCf*solider->AttackDamage;
				/*buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
				buffdata->ResourceName = attack->ResourceName2;*/
			}
			buffdata->Target = sol;
			buffdata->HitVoice_ = attack->HitVoice;
			CBuff * buff = new CBuff(buffdata);
			CBattleObjectManager::GetInstance()->AddBuffObject(buff);
		}
		CBuffData * buffdata1 = new CBuffData();
		buffdata1->AttackType = 1;
		buffdata1->ContinueTime = 0;
		buffdata1->attackPoint = attack->AttackPoint;
		buffdata1->From = solider;
		buffdata1->Damage = 0;
		buffdata1->Target = solider->AttackTarget;
		buffdata1->HitVoice_ = attack->HitVoice;
		buffdata1->ResourceFrameCount = attack->ResourceFrameCount2;
		buffdata1->ResourceName = attack->ResourceName2;
		CBuff * buff = new CBuff(buffdata1);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
		solider->AttackTarget = nullptr;
	}
	else
	{
		CBuffData*buffdata = new CBuffData();
		buffdata->AttackType = 1;
		buffdata->Damage = attack->HurtCf*solider->AttackDamage;
		buffdata->ContinueTime = 0;
		buffdata->attackPoint = attack->AttackPoint;

		buffdata->From = solider;
		if (attack->EffectId == 1)
		{
			buffdata->Damage = attack->HurtCf*solider->AttackDamage;
		}
		if (attack->EffectId == 2)
		{
			buffdata->ContinueTime = attack->EffectValue[0];
			buffdata->SpeedCf = attack->EffectValue[1];
			buffdata->AttackInveralCf = attack->EffectValue[2];
			buffdata->ResourceFrameCount = attack->ResourceFrameCount3;
			buffdata->ResourceName = attack->ResourceName3;
		}
		else if (attack->EffectId == 3)
		{
			buffdata->ContinueTime = attack->EffectValue[0];
			buffdata->AttackCf = attack->EffectValue[1];
			buffdata->ResourceFrameCount = attack->ResourceFrameCount3;
			buffdata->ResourceName = attack->ResourceName3;
		}
		else
		{
			buffdata->Damage = attack->HurtCf*solider->AttackDamage;
			buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
			buffdata->ResourceName = attack->ResourceName2;
		}
		if (attack->TargetRank == 2)
		{
			buffdata->Target = solider;
		}
		else
			buffdata->Target = solider->AttackTarget;
		buffdata->HitVoice_ = attack->HitVoice;
		CBuff * buff = new CBuff(buffdata);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}


}
void CSkillManager::OnAttackByType2(CSolider* solider, CSkillData* attack)
{
	if (attack->EffectId != 0)
	{
		CBuffData* data1 = new CBuffData();

		data1->AttackType = 1;
		data1->From = solider;
		data1->Target = solider->AttackTarget;
		if (attack->EffectId == 1)
		{
			data1->Damage = attack->HurtCf*solider->AttackDamage;
		}
		if (attack->EffectId == 2)
		{
			data1->ContinueTime = attack->EffectValue[0];
			data1->SpeedCf = attack->EffectValue[1];
			data1->AttackInveralCf = attack->EffectValue[2];
			data1->ResourceFrameCount = attack->ResourceFrameCount3;
			data1->ResourceName = attack->ResourceName3;
		}
		else if (attack->EffectId == 3)
		{
			data1->ContinueTime = attack->EffectValue[0];
			data1->AttackCf = attack->EffectValue[1];
			data1->ResourceFrameCount = attack->ResourceFrameCount3;
			data1->ResourceName = attack->ResourceName3;
		}
		data1->attackPoint = attack->AttackPoint;
		data1->HitVoice_ = attack->HitVoice;
		CBuff *buff2 = new CBuff(data1);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff2);
	}

	CBuffData * buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->BuffType = E_Buff_LowBlood;
	buffdata->ContinueTime = 0;
	buffdata->attackPoint = attack->AttackPoint;
	buffdata->From = solider;
	buffdata->Damage = solider->AttackDamage*attack->HurtCf;
	buffdata->Target = solider->AttackTarget;
	buffdata->HitVoice_ = attack->HitVoice;
	buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
	buffdata->ResourceName = attack->ResourceName2;

	CAttackData* data = new CAttackData();
	data->AttackPoint = attack->AttackPoint;
	data->TargetRank = attack->TargetRank;
	data->TargetType = attack->TargetType;
	data->BulletType = attack->BulletType;
	data->BulletValue[0] = attack->BulletValue[0];
	data->BulletValue[1] = attack->BulletValue[1];
	data->BulletValue[2] = attack->BulletValue[2];
	data->EffectId = attack->EffectId;
	data->HitVoice = attack->HitVoice;
	data->AttackVoice = attack->AttackVoice;
	data->ResourceName1 = attack->ResourceName1;
	data->ResourceFrameCount1 = attack->ResourceFrameCount1;
	data->ResourceName2 = attack->ResourceName2;
	data->ResourceFrameCount2 = attack->ResourceFrameCount2;
	data->ResourceName3 = attack->ResourceName3;
	data->ResourceFrameCount3 = attack->ResourceFrameCount3;

	CBullet* buttlet = new CBullet(data, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY(), buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(buttlet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(buttlet);
}
void CSkillManager::OnAttackByType3(CSolider* solider, CSkillData* attack)
{
	Vector<CSolider*>list = GetList(solider, attack);
	for (CSolider* sol : list)
	{
		CBuffData* data = new CBuffData();
		data->AttackType = 1;
		data->attackPoint = attack->AttackPoint;
		if (attack->EffectId == 1)
		{
			data->Damage = attack->HurtCf*solider->AttackDamage;
		}
		if (attack->EffectId == 2)
		{
			data->ContinueTime = attack->EffectValue[0];
			data->SpeedCf = attack->EffectValue[1];
			data->AttackInveralCf = attack->EffectValue[2];
			data->ResourceFrameCount = attack->ResourceFrameCount3;
			data->ResourceName = attack->ResourceName3;
		}
		else if (attack->EffectId == 3)
		{
			data->ContinueTime = attack->EffectValue[0];
			data->AttackCf = attack->EffectValue[1];
			data->ResourceFrameCount = attack->ResourceFrameCount3;
			data->ResourceName = attack->ResourceName3;
		}
		else
		{
			data->Damage = attack->HurtCf*solider->AttackDamage;
			data->ResourceFrameCount = attack->ResourceFrameCount2;
			data->ResourceName = attack->ResourceName2;
		}
		data->From = solider;
		data->Target = sol;
		data->HitVoice_ = attack->HitVoice;
		CBuff * buff = new CBuff(data);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
}
void CSkillManager::OnAttackByType4(CSolider* solider, CSkillData* attack)
{
	CBuffData*buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->attackPoint = attack->AttackPoint;
	if (attack->EffectId == 1 || attack->EffectId == 0)
	{
		buffdata->Damage = attack->HurtCf*solider->AttackDamage;
	}
	if (attack->EffectId == 2)
	{
		buffdata->ContinueTime = attack->EffectValue[0];
		buffdata->SpeedCf = attack->EffectValue[1];
		buffdata->AttackInveralCf = attack->EffectValue[2];
	}
	else if (attack->EffectId == 3)
	{
		buffdata->ContinueTime = attack->EffectValue[0];
		buffdata->AttackCf = attack->EffectValue[1];
	}
	buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
	buffdata->ResourceName = attack->ResourceName2;
	buffdata->From = solider;
	buffdata->Target = solider->AttackTarget;
	buffdata->HitVoice_ = attack->HitVoice;
	CAttackData * data = new CAttackData();
	data->AttackPoint = attack->AttackPoint;
	data->TargetRank = attack->TargetRank;
	data->TargetType = attack->TargetType;
	data->BulletType = attack->BulletType;
	data->BulletValue[0] = attack->BulletValue[0];
	data->BulletValue[1] = attack->BulletValue[1];
	data->BulletValue[2] = attack->BulletValue[2];
	data->EffectId = attack->EffectId;
	data->HitVoice = attack->HitVoice;
	data->AttackVoice = attack->AttackVoice;
	data->ResourceName1 = attack->ResourceName1;
	data->ResourceFrameCount1 = attack->ResourceFrameCount1;
	data->ResourceName2 = attack->ResourceName2;
	data->ResourceFrameCount2 = attack->ResourceFrameCount2;
	data->ResourceName3 = attack->ResourceName3;
	data->ResourceFrameCount3 = attack->ResourceFrameCount3;
	CLineBullet* bullet = new CLineBullet(data, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY()
		, buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(bullet);

}
void CSkillManager::OnAttackByType5(CSolider* solider, CSkillData* data)
{

}
void CSkillManager::OnAttackByType6(CSolider* solider, CSkillData* data)
{

}
void CSkillManager::OnAttackByType7(CSolider* solider, CSkillData* attack)
{
	CBuffData* buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->From = solider;
	buffdata->Target = solider->AttackTarget;
	buffdata->ContinueTime = 0;
	buffdata->Damage = solider->AttackDamage*attack->HurtCf;
	buffdata->HitVoice_ = attack->HitVoice;
	buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
	buffdata->ResourceName = attack->ResourceName2;
	CAttackData * data = new CAttackData();
	data->AttackPoint = attack->AttackPoint;
	data->TargetRank = attack->TargetRank;
	data->TargetType = attack->TargetType;
	data->BulletType = attack->BulletType;
	data->BulletValue[0] = attack->BulletValue[0];
	data->BulletValue[1] = attack->BulletValue[1];
	data->BulletValue[2] = attack->BulletValue[2];
	data->EffectId = attack->EffectId;
	data->HitVoice = attack->HitVoice;
	data->AttackVoice = attack->AttackVoice;
	data->ResourceName1 = attack->ResourceName1;
	data->ResourceFrameCount1 = attack->ResourceFrameCount1;
	data->ResourceName2 = attack->ResourceName2;
	data->ResourceFrameCount2 = attack->ResourceFrameCount2;
	data->ResourceName3 = attack->ResourceName3;
	data->ResourceFrameCount3 = attack->ResourceFrameCount3;
	CSustainBullet* bullet = new CSustainBullet(data, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY(), buffdata, solider->AttackTarget, solider->Ranks, 2);
	//CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(bullet);

}
void CSkillManager::OnAttackByType8(CSolider* solider, CSkillData* attack)
{
	CBuffData* buffdata1 = nullptr;
	if (attack->EffectId != 0)
	{
		buffdata1 = new CBuffData();
		if (attack->EffectId == 1 || attack->EffectId == 0)
		{
			buffdata1->Damage = attack->HurtCf*solider->AttackDamage;
		}
		if (attack->EffectId == 2)
		{
			buffdata1->ContinueTime = attack->EffectValue[0];
			buffdata1->SpeedCf = attack->EffectValue[1];
			buffdata1->AttackInveralCf = attack->EffectValue[2];
		}
		else if (attack->EffectId == 3)
		{
			buffdata1->ContinueTime = attack->EffectValue[0];
			buffdata1->AttackCf = attack->EffectValue[1];
		}

		buffdata1->AttackType = 1;
		buffdata1->From = solider;
		buffdata1->attackPoint = 1;
		buffdata1->Target = solider->AttackTarget;
		buffdata1->HitVoice_ = attack->HitVoice;
		buffdata1->ResourceFrameCount = attack->ResourceFrameCount3;
		buffdata1->ResourceName = attack->ResourceName3;
	}
	CBuffData* buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->From = solider;
	buffdata->Target = solider->AttackTarget;
	buffdata->ContinueTime = 0;
	buffdata->attackPoint = 1;
	buffdata->Damage = solider->AttackDamage*attack->HurtCf;
	buffdata->HitVoice_ = attack->HitVoice;
	buffdata->NextBuff = buffdata1;
	buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
	buffdata->ResourceName = attack->ResourceName2;
	CAttackData * data = new CAttackData();
	data->AttackPoint = attack->AttackPoint;
	data->TargetRank = attack->TargetRank;
	data->TargetType = attack->TargetType;
	data->BulletType = attack->BulletType;
	data->BulletValue[0] = attack->BulletValue[0];
	data->BulletValue[1] = attack->BulletValue[1];
	data->BulletValue[2] = attack->BulletValue[2];
	data->EffectId = attack->EffectId;
	data->HitVoice = attack->HitVoice;
	data->AttackVoice = attack->AttackVoice;
	data->ResourceName1 = attack->ResourceName1;
	data->ResourceFrameCount1 = attack->ResourceFrameCount1;
	data->ResourceName2 = attack->ResourceName2;
	data->ResourceFrameCount2 = attack->ResourceFrameCount2;
	data->ResourceName3 = attack->ResourceName3;
	data->ResourceFrameCount3 = attack->ResourceFrameCount3;

	CLinkBullet* bullet = new CLinkBullet(data, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY(), buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(bullet);
}
void  CSkillManager::OnAttackByType9(CSolider* solider, CSkillData* attack)
{

}