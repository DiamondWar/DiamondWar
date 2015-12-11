#include "Solider.h"
#include "BattleObjectManager.h"
#include "CGlobleConfig.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "HurtShow.h"
#include "SkillManager.h"
#include "Buff.h"

CSolider::CSolider(int id, int type, int rank)
{
	Data_ = CSoliderConfig::GetInstance()->GetItemById(id);
	AttackData_ = CSkillConfig::GetInstance()->GetItemById(Data_->AttackId);
	SKillData_ = CSkillConfig::GetInstance()->GetItemById(Data_->SkillId);
	ResourceName = Data_->ResourceName;
	if (rank == 1)
		Init_x = 10;
	else
		Init_x = 1900;
	if (Data_->SoliderType == 3)
		Init_y = CCGlobleConfig::COMMON_SKY_POINT;
	else

		Init_y = CCGlobleConfig::COMMON_LOAD_POINT;
	DownLoadType = type;
	Ranks = rank;
	RangeR_ = Data_->RangeR;
	AttakRange = Data_->AttackRange;///CCGlobleConfig::COMMON_VALUE;
	AttakInveral = Data_->AttackInterval*CCGlobleConfig::COMMON_ATTACK_VALUE;
	MoveSpeed = Data_->MoveSpeed*CCGlobleConfig::COMMON_VALUE;
	CCLOG("MoveSpeed===  %d, attackRange === %f ,AttackInveral===%d  ", MoveSpeed, AttakRange, AttakInveral);
	init_AttackInveral = AttakInveral;
	Init_AttackRange = AttakRange;
	Init_MoveSpeed = MoveSpeed;
	InitObj();
	AttackDamage = Data_->Attack;

}


CSolider::~CSolider()
{
}
void CSolider::OnResourceLoadComplete()
{
	Obj->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	Obj->setPosition(Init_x, Init_y);
	if (Ranks != 1)
	{
		Obj->setRotationSkewY(180);
	}
	OnRun();
}
void CSolider::Update()
{
	__super::Update();
	switch (OpreateType)
	{
	case ESoliderOpreate_Idle:
		NowTime = CCGlobleConfig::GetCurrntTime();
		if (NowTime > LastAttackTime + AttakInveral)
		{
			LastAttackTime = NowTime;
			CheckAttackOrSkill();
		}
		if (isShowHurt == true)
		{
			if (CCGlobleConfig::Game_time > lastShowHurtTime + 10)
			{
				isShowHurt = false;
				ShowHurt();
			}
			else
			{
				ShowHurt();
			}
		}

		break;
	case ESoliderOpreate_Walk:
		if (Ranks == 1)
			Obj->setPosition(Obj->getPosition().x + MoveSpeed, Obj->getPosition().y);
		else
			Obj->setPosition(Obj->getPosition().x - MoveSpeed, Obj->getPosition().y);
		if (AttackTarget != nullptr)
		{
			CheckAttackOrSkill();
			NowTime = CCGlobleConfig::GetCurrntTime();
			LastAttackTime = NowTime;
		}
		else
		{
			CheckEnemyInRange();
		}
		break;
	case ESoliderOpreate_Attack:
		return;
		break;
	case ESoliderOpreate_Skill:
		break;
	case ESoliderOpreate_Hurt:
		break;
	default:
		break;
	}

}

//动作播放完成
void CSolider::OnHurtActionComplete()
{
	OnIdle();
}
void CSolider::OnAttackActionComplete()
{
	OnIdle();
}
void CSolider::OnSkillActionComplete()
{
	OnIdle();
}
bool CSolider::CheckEnemyInRange()
{
	CSolider* Sol = CBattleObjectManager::GetInstance()->GetEnemyByRange((float)Ranks, (float)AttakRange, (float)RangeR_, (float)Obj->getPosition().x, (float)Obj->getPosition().y);
	if (Sol != nullptr)
	{
		AttackTarget = Sol;
		return true;
	}
	return false;
}
void CSolider::CheckFriendInRange()
{
	/*CSolider* Sol = CBattleObjectManager::GetInstance()->GetEnemyByRange((float)Ranks, (float)AttakRange, (float)Obj->getPosition().x, (float)Obj->getPosition().y);
	if (Sol != nullptr)
	{
	AttackTarget = Sol;
	}*/
}
void CSolider::CheckAttackOrSkill()
{
	CCLOG("ID: %d AttackNum ==== %d",Data_->ID, AttackNum);
	if (AttackNum >= SKillData_->CoolTime)
	{
	AttackNum = 0;
	OnSkill();
	}
	else
	{
	AttackNum++;
	OnAttack();
	}
	//OnSkill();
}
void CSolider::OnIdle()
{
	OpreateType = ESoliderOpreate_Idle;
	__super::OnIdle();
}
void CSolider::OnRun()
{
	OpreateType = ESoliderOpreate_Walk;
	__super::OnRun();
}
void CSolider::OnAttack()
{
	if (AttackData_->BulletType <= 1)
	{
		AttackTarget->GetDamage(AttackData_->HurtCf*AttackDamage,3);
	}
	else
	{
		CBuffData * buffdata = new CBuffData();
		buffdata->Damage = AttackData_->HurtCf*AttackDamage;
		buffdata->Target = AttackTarget;
		CBullet* buttlet = new CBullet(AttackData_, Obj->getPosition().x, Obj->getPosition().y, buffdata, AttackTarget, Ranks, 2);
		Obj->getParent()->addChild(buttlet->Obj);
		CBattleObjectManager::GetInstance()->AddBulletObject(buttlet);
	}
	OpreateType = ESoliderOpreate_Attack;
	__super::OnAttack();
}
void CSolider::OnHurt()
{
	OpreateType = ESoliderOpreate_Hurt;
	__super::OnHurt();
}
void  CSolider::GetBuff(CBuffData* data)
{
	if (data->Damage != 0)
	{
		GetDamage(data->Damage,3); 
	}
	else
	{
		if (data->AttackInveralCf != 0)
		{
			GetAttackSpeedCf(data->AttackInveralCf); 
		}
		if (data->SpeedCf != 0)
		{
			GetMoveSpeedCf(data->SpeedCf);
		}
		if (data->AttackCf != 0)
		{
			GetAttackCf(data->AttackCf);
		}
		if (data->AttackRangeCf != 0)
		{
			GetAttackRangeCf(data->AttackRangeCf);
		}
	}
	
}
void CSolider::GetDamage(int damage,int type)
{
	
	CCLOG("Damange:   %d %.1f , AttackInveralCf = %.1f , MoveSpeedCf = %.1f", damage, AttackCf,AttakInveralCf,MoveSpeedCf);
	damage = damage - damage*AttackCf;
	if (damage == 0)
		return;
	isShowHurt = true;
	lastShowHurtTime = CCGlobleConfig::Game_time;
	CHurtShow *hurt = new CHurtShow();
	hurt->SetFont(3);
	hurt->ShowLabel(damage, Obj);
	CBattleObjectManager::GetInstance()->AddHurtShowObject(hurt);
}
void CSolider::GetMoveSpeedCf(float cf)
{
	MoveSpeedCf += cf;
	MoveSpeed += Init_MoveSpeed + Init_MoveSpeed*MoveSpeedCf;
}
void CSolider::GetAttackSpeedCf(float cf)
{
	AttakInveralCf +=cf;
	AttakInveral = init_AttackInveral + init_AttackInveral *AttakInveralCf;
}
void  CSolider::GetAttackRangeCf(float cf)
{
	AttackRangeCf += cf;
	AttakRange = Init_AttackRange + Init_AttackRange*AttackRangeCf;
}
void CSolider::GetAttackCf(float cf)
{
	AttackCf += cf;
}
void CSolider::ShowHurt()
{
	if (isShowHurt == true)
		Obj->setColor(cocos2d::Color3B::GRAY);
	else
		Obj->setColor(cocos2d::Color3B::WHITE);
}
void CSolider::OnSkill()
{
	if (SKillData_->BulletType >= 1)
	{
		CSkillManager::GetInstance()->ChoseSkill(SKillData_, this);
	}
	OpreateType = ESoliderOpreate_Skill;
	__super::OnSkill();
}
