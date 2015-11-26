#include "Solider.h"
#include "BattleObjectManager.h"
#include "CGlobleConfig.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "HurtShow.h"
CSolider::CSolider(int id,std::string name, int x, int y, int type, int range,int rank)
{
	Data_ = CSoliderConfig::GetInstance()->GetItemById(id);
	AttackData_ = CSkillConfig::GetInstance()->GetItemById(Data_->AttackId);
	SKillData_ = CSkillConfig::GetInstance()->GetItemById(Data_->SkillId);
	ResourceName = name;
	Init_x = x;
	Init_y = y;
	DownLoadType = type;
	SkillName = name;
	Ranks = rank;
	RangeR_ = 200;
	AttakRange = range;
	AttakInveral = Data_->AttackRange*CCGlobleConfig::COMMON_ATTACK_VALUE;
	MoveSpeed = Data_->MoveSpeed*CCGlobleConfig::COMMON_VALUE;
	CCLOG("MoveSpeed===  %d", MoveSpeed);
	InitObj();
	AttackDamage = Data_->Attack;
	
}


CSolider::~CSolider()
{
}
void CSolider::OnResourceLoadComplete()
{
	Obj->setPosition(Init_x, Init_y);
	Obj->setScale(0.5, 0.5);
	if (Ranks != 1)
	{
		Obj->setRotationSkewY(180);
	}
	// 创建物体，并且物体的形状为圆形，第一参数为半径，第二个参数为物体材质
	//第三个参数为边的厚度,就是在Debug模式下看到的物体外面线条的厚度，默认为0 
	cocos2d::PhysicsBody* ballBodyOne = cocos2d::PhysicsBody::createBox(cocos2d::Size(200, 200), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
	//是否设置物体为静态 
	//ballBody->setDynamic(false); 
	//设置物体的恢复力 
	ballBodyOne->getShape(0)->setRestitution(0.0f);
	//设置物体的摩擦力 
	ballBodyOne->getShape(0)->setFriction(0.0f);
	//设置物体密度 
	ballBodyOne->getShape(0)->setDensity(0.0f);
	//设置质量 
	//ballBodyOne->getShape(0)->setMass(5000); 
	//设置物体是否受重力系数影响 
	ballBodyOne->setGravityEnable(false);
	//把物体添加到精灵中 
	Obj->setPhysicsBody(ballBodyOne);
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
