#include "AttackManager.h"
#include "CGlobleConfig.h"
#include "BattleObjectManager.h"
#include "Buff.h"
#include "LinkBullet.h"
#include "LineBullet.h"
#include "AudioManager.h"
#include "GameSceneControl.h"
USING_NS_CC;
CAttackManager* CAttackManager::Instance_ = nullptr;
CAttackManager::CAttackManager()
{
}
CAttackManager* CAttackManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CAttackManager();
	return Instance_;
}

CAttackManager::~CAttackManager()
{
}

void CAttackManager::OnAttack(CSolider* solider, CAttackData* data)
{
	CAudioManager::GetInstance()->PlayerVoice(data->AttackVoice);
	if (data->BulletType == 1)
	{
		OnAttackByType1(solider, data);
	}
	else if (data->BulletType == 2)
	{
		OnAttackByType2(solider, data);
	}
	else if (data->BulletType == 3)
	{
		OnAttackByType3(solider, data);
	}
	else if (data->BulletType == 4)
	{
		OnAttackByType4(solider, data);
	}
	else if (data->BulletType == 5)
	{
		OnAttackByType5(solider, data);
	}
	else if (data->BulletType == 6)
	{
		OnAttackByType6(solider, data);
	}
	else if (data->BulletType == 7)
	{
		OnAttackByType7(solider, data);
	}
	else if (data->BulletType == 8)
	{
		OnAttackByType8(solider, data);
	}
}
void CAttackManager::OnAttackByType1(CSolider* solider, CAttackData* attack)
{

	CBuffData* data = new CBuffData();
	data->ContinueTime = 0;
	data->AttackType = 1;
	data->From = solider;
	data->Target = solider->AttackTarget;
	data->Damage = solider->AttackDamage;
	data->attackPoint = attack->AttackPoint;
	if (attack->ResourceFrameCount2 != 0)
	{
		data->ResourceFrameCount = attack->ResourceFrameCount2;
		data->ResourceName = attack->ResourceName2;
	}
	else
	{
		data->ResourceFrameCount = 1;
		data->ResourceName = "Bullet_common_1";
	}

	CBuff *buff = new CBuff(data);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);

	CBuffData* data1 = new CBuffData();
	data1->ContinueTime = 0;
	data1->AttackType = 1;
	data1->From = solider;
	data1->Target = solider;
	data1->Damage = 0;
	data1->attackPoint = 5;
	data1->ResourceFrameCount = attack->ResourceFrameCount3;
	data1->ResourceName = attack->ResourceName3;
	data1->HitVoice_ = attack->HitVoice;
	CBuff *buff2 = new CBuff(data1);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff2);
}
void CAttackManager::OnAttackByType2(CSolider* solider, CAttackData* attack)
{
	if (attack->ResourceFrameCount3 != 0)
	{
		CBuffData* data1 = new CBuffData();
		data1->ContinueTime = 0;
		data1->AttackType = 1;
		data1->From = solider;
		data1->Target = solider;
		data1->Damage = 0;
		data1->attackPoint = 6;
		data1->ResourceFrameCount = attack->ResourceFrameCount3;
		data1->ResourceName = attack->ResourceName3;
		CBuff *buff2 = new CBuff(data1);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff2);
	}

	CBuffData * buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->BuffType = E_Buff_LowBlood;
	buffdata->ContinueTime = 0;
	buffdata->attackPoint = 1;
	buffdata->From = solider;
	buffdata->Damage = solider->AttackDamage;
	buffdata->Target = solider->AttackTarget;
	buffdata->HitVoice_ = attack->HitVoice;
	if (attack->ResourceFrameCount2 == 0)
	{
		buffdata->ResourceFrameCount = 1;
		buffdata->ResourceName = "Bullet_common_1";
	}
	else
	{
		buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
		buffdata->ResourceName = attack->ResourceName2;
	}

	CBullet* buttlet = new CBullet(attack, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY(), buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(buttlet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(buttlet);
}
void CAttackManager::OnAttackByType3(CSolider* solider, CAttackData* attack)
{
	Vector<CSolider*> list;
	int range = attack->BulletValue[0];
	if (attack->TargetType == 3)
	{
		list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->CenterPoint_->getPosition().x + solider->Obj->getPosition().x,
			solider->CenterPoint_->getPosition().y + solider->Obj->getPosition().y);
	}
	else if (attack->TargetType == 2)
	{
		list = CBattleObjectManager::GetInstance()->GetFeiXingEnemyListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->CenterPoint_->getPosition().x + solider->Obj->getPosition().x,
			solider->CenterPoint_->getPosition().y + solider->Obj->getPosition().y);
	}
	else if (attack->TargetType == 1)
	{
		list = CBattleObjectManager::GetInstance()->GetLuDiEnemyListByRange(solider->Ranks, solider->AttakRange, solider->RangeR_, solider->CenterPoint_->getPosition().x + solider->Obj->getPosition().x,
			solider->CenterPoint_->getPosition().y + solider->Obj->getPosition().y);
	}
	for (CSolider* sol : list)
	{
		CBuffData * buffdata = new CBuffData();
		buffdata->AttackType = 1;
		buffdata->BuffType = E_Buff_LowBlood;
		buffdata->ContinueTime = 0;
		buffdata->attackPoint = 1;
		buffdata->From = solider;
		buffdata->Damage = solider->AttackDamage;
		buffdata->Target = solider->AttackTarget;
		buffdata->HitVoice_ = attack->HitVoice;
		if (attack->ResourceFrameCount2 == 0)
		{
			buffdata->ResourceFrameCount = 1;
			buffdata->ResourceName = "Bullet_common_1";
		}
		else
		{
			buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
			buffdata->ResourceName = attack->ResourceName2;
		}
		CBuff *buff2 = new CBuff(buffdata);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff2);
		sol->GetDamage(sol->AttackDamage, 3);
	}
	if (attack->ResourceFrameCount3 != 0)
	{
		CBuffData* data1 = new CBuffData();
		data1->ContinueTime = 0;
		data1->AttackType = 1;
		data1->From = solider;
		data1->Target = solider;
		data1->Damage = 0;
		data1->attackPoint = 6;
		data1->ResourceFrameCount = attack->ResourceFrameCount3;
		data1->ResourceName = attack->ResourceName3;
		CBuff *buff2 = new CBuff(data1);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff2);
	}
}
void CAttackManager::OnAttackByType4(CSolider* solider, CAttackData* data)
{
	CBuffData *buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->Damage = solider->AttackDamage;
	buffdata->ContinueTime = 0;
	buffdata->ResourceFrameCount = data->ResourceFrameCount2;
	buffdata->ResourceName = data->ResourceName2;
	buffdata->HitVoice_ = data->HitVoice;
	CLineBullet* bullet = new CLineBullet(data, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY()
		, buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(bullet);
}
void CAttackManager::OnAttackByType5(CSolider* solider, CAttackData* data)
{

}
void CAttackManager::OnAttackByType6(CSolider* solider, CAttackData* attack)
{
	if (attack->ResourceFrameCount3 != 0)
	{
		CBuffData* data1 = new CBuffData();
		data1->ContinueTime = 0;
		data1->AttackType = 1;
		data1->From = solider;
		data1->Target = solider;
		data1->Damage = 0;
		data1->attackPoint = 6;
		data1->ResourceFrameCount = attack->ResourceFrameCount3;
		data1->ResourceName = attack->ResourceName3;
		CBuff *buff2 = new CBuff(data1);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff2);
	}

	CBuffData * buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->BuffType = E_Buff_LowBlood;
	buffdata->ContinueTime = 0;
	buffdata->attackPoint = 1;
	buffdata->From = solider;
	buffdata->Damage = solider->AttackDamage;
	buffdata->Target = solider->AttackTarget;
	if (attack->ResourceFrameCount2 == 0)
	{
		buffdata->ResourceFrameCount = 1;
		buffdata->ResourceName = "Bullet_common_1";
	}
	else
	{
		buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
		buffdata->ResourceName = attack->ResourceName2;
	}
	buffdata->HitVoice_ = attack->HitVoice;
	CBullet* buttlet = new CBullet(attack, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY() + 400, buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(buttlet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(buttlet);
}
void CAttackManager::OnAttackByType7(CSolider* solider, CAttackData* data)
{
	CBuffData *buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->From = solider;
	buffdata->Target = solider;
	buffdata->AttackInveralCf = -1000;
	buffdata->ContinueTime = 5;
	CBuff* buff = new CBuff(buffdata);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
}
void CAttackManager::OnAttackByType8(CSolider* solider, CAttackData* attack)
{

	CBuffData* buffdata = new CBuffData();
	buffdata->AttackType = 1;
	buffdata->From = solider;
	buffdata->Target = solider->AttackTarget;
	buffdata->ContinueTime = 0;
	buffdata->Damage = solider->AttackDamage;
	buffdata->HitVoice_ = attack->HitVoice;
	buffdata->ResourceFrameCount = attack->ResourceFrameCount2;
	buffdata->ResourceName = attack->ResourceName2;
	CLinkBullet* bullet = new CLinkBullet(attack, solider->GetBulletPointToBulletX(), solider->GetBulletPointToBulletY(), buffdata, solider->AttackTarget, solider->Ranks, 2);
	CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(bullet);
}