#include "Solider.h"
#include "BattleObjectManager.h"
#include "CGlobleConfig.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "HurtShow.h"
CSolider::CSolider(int id, int type,int rank)
{
	Data_ = CSoliderConfig::GetInstance()->GetItemById(id);
	AttackData_ = CSkillConfig::GetInstance()->GetItemById(Data_->AttackId);
	SKillData_ = CSkillConfig::GetInstance()->GetItemById(Data_->SkillId);
	ResourceName = Data_->ResourceName;
	if (rank == 1)
		Init_x = 10;
	else
		Init_x = 1900;
	if (Data_->Type == 3)
		Init_y = CCGlobleConfig::COMMON_SKY_POINT;
	else 

		Init_y = CCGlobleConfig::COMMON_LOAD_POINT;
	DownLoadType = type;
	Ranks = rank;
	RangeR_ = Data_->RangeR;
	AttakRange = Data_->AttackRange;///CCGlobleConfig::COMMON_VALUE;
	AttakInveral = Data_->AttackInterval*CCGlobleConfig::COMMON_ATTACK_VALUE;
	MoveSpeed = Data_->MoveSpeed*CCGlobleConfig::COMMON_VALUE;
	CCLOG("MoveSpeed===  %d, attackRange === %f ,AttackInveral===%d  ", MoveSpeed, AttakRange,AttakInveral);
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
	// �������壬�����������״ΪԲ�Σ���һ����Ϊ�뾶���ڶ�������Ϊ�������
	//����������Ϊ�ߵĺ��,������Debugģʽ�¿������������������ĺ�ȣ�Ĭ��Ϊ0 
	cocos2d::PhysicsBody* ballBodyOne = cocos2d::PhysicsBody::createCircle(AttakRange, cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
	//�Ƿ���������Ϊ��̬ 
	//ballBody->setDynamic(false); 
	//��������Ļָ��� 
	ballBodyOne->getShape(0)->setRestitution(0.0f);
	//���������Ħ���� 
	ballBodyOne->getShape(0)->setFriction(0.0f);
	//���������ܶ� 
	ballBodyOne->getShape(0)->setDensity(0.0f);
	//�������� 
	//ballBodyOne->getShape(0)->setMass(5000); 
	//���������Ƿ�������ϵ��Ӱ�� 
	ballBodyOne->setGravityEnable(false);
	//��������ӵ������� 
	//Obj->setPhysicsBody(ballBodyOne);
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
			OnAttack();
		}
		if (isShowHurt == true)
		{
			if (CCGlobleConfig::Game_time > lastShowHurtTime +10)
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
			CCLOG("OnAttack");
			OnAttack();
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

//�����������
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
void CSolider::OnIdle()
{
	OpreateType= ESoliderOpreate_Idle;
	__super::OnIdle();
}
void CSolider::OnRun()
{
	OpreateType = ESoliderOpreate_Walk;
	__super::OnRun();
}
void CSolider::OnAttack()
{
	CBullet* buttlet = new CBullet(1, "Bullet", Obj->getPosition().x, Obj->getPosition().y, AttackDamage, AttackTarget, Ranks, 2);
	Obj->getParent()->addChild(buttlet->Obj);
	CBattleObjectManager::GetInstance()->AddBulletObject(buttlet);
	OpreateType = ESoliderOpreate_Attack;
	__super::OnAttack();
}
void CSolider::OnHurt()
{
	OpreateType = ESoliderOpreate_Hurt;
	__super::OnHurt();
}
void  CSolider::GetDamage(int damage)
{
	CCLOG("Damange:   %d", damage);
	isShowHurt = true;
	lastShowHurtTime = CCGlobleConfig::Game_time;
	CHurtShow *hurt = new CHurtShow();
	hurt->SetFont(3);
	hurt->ShowLabel(damage,Obj);
	CBattleObjectManager::GetInstance()->AddHurtShowObject(hurt);
}
void CSolider::ShowHurt()
{
	if (isShowHurt== true)
	Obj->setColor(cocos2d::Color3B::GRAY);
	else 
		Obj->setColor(cocos2d::Color3B::WHITE);
}
void CSolider::OnSkill()
{
	OpreateType = ESoliderOpreate_Skill;
	__super::OnSkill();
}
