#include "Solider.h"
#include "BattleObjectManager.h"
#include "CGlobleConfig.h"
#include "cocos2d.h"
#include "Bullet.h"

CSolider::CSolider(std::string name, int x, int y, int type, int rank,int range)
{
	ResourceName = name;
	Init_x = x;
	Init_y = y;
	DownLoadType = type;
	SkillName = name;
	Ranks = rank;
	RangeR_ = 200;
	AttakRange = range;
	InitObj();
	
}


CSolider::~CSolider()
{
}
void CSolider::OnResourceLoadComplete()
{
	CCLOG("-------------------------------------------");
	Obj->setPosition(Init_x, Init_y);
	Obj->setScale(0.5, 0.5);
	if (Ranks != 1)
	{
		Obj->setRotationSkewY(180);
	}
	// �������壬�����������״ΪԲ�Σ���һ����Ϊ�뾶���ڶ�������Ϊ�������
	//����������Ϊ�ߵĺ��,������Debugģʽ�¿������������������ĺ�ȣ�Ĭ��Ϊ0 
	cocos2d::PhysicsBody* ballBodyOne = cocos2d::PhysicsBody::createBox(cocos2d::Size(200, 200), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);
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
		break;
	case ESoliderOpreate_Walk:
		if (Ranks == 1)
			Obj->setPosition(Obj->getPosition().x + speed_x, Obj->getPosition().y + spped_y);
		else
			Obj->setPosition(Obj->getPosition().x - speed_x, Obj->getPosition().y - spped_y);

		if (Obj->getPosition().x > cocos2d::Director::getInstance()->getVisibleSize().width)
		{
			speed_x = -speed_x;
		}
		else if (Obj->getPosition().x <= 0)
		{
			speed_x = -speed_x;
		}

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
	CCLOG("OnAttackActionComplete");
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
	CBullet* buttlet = new CBullet(1, "Bullet", Obj->getPosition(), AttackTarget, Ranks, 2);
	Obj->addChild(buttlet->Obj);
	CBattleObjectManager::GetInstance()->AddObject(buttlet);
	OpreateType = ESoliderOpreate_Attack;
	__super::OnAttack();
}
void CSolider::OnHurt()
{
	OpreateType = ESoliderOpreate_Hurt;
	__super::OnHurt();
}
void CSolider::OnSkill()
{
	OpreateType = ESoliderOpreate_Skill;
	__super::OnSkill();
}
