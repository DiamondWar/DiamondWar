#include "Solider.h"
#include "BattleObjectManager.h"
#include "CGlobleConfig.h"
#include "cocos2d.h"
#include "Bullet.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "AttackConfig.h"
#include "HurtShow.h"
#include "SkillManager.h"
#include "Buff.h"
#include "AttackManager.h"
#include "GameSceneControl.h"
USING_NS_CC;
CSolider::CSolider(int id, int type, int rank, float level)
{
	Data_ = CSoliderConfig::GetInstance()->GetItemById(id);
	AttackData_ = CAttackConfig::GetInstance()->GetItemById(Data_->AttackId);
	SKillData_ = CSkillConfig::GetInstance()->GetItemById(Data_->SkillId);
	ResourceName = Data_->ResourceName;
	if (rank == 1)
		Init_x = CBattleObjectManager::GetInstance()->GetFirstRanksBoss()->Obj->getPositionX();
	else
		Init_x = CBattleObjectManager::GetInstance()->GetSecondRanksBoss()->Obj->getPositionX()-100;
	if (Data_->SoliderType == 3)
		Init_y = CCGlobleConfig::COMMON_SKY_POINT;
	else

		Init_y = CCGlobleConfig::COMMON_LOAD_POINT;
	DownLoadType = type;
	Ranks = rank;
	RangeR_ = Data_->RangeR;
	AttakRange = Data_->AttackRange*CCGlobleConfig::COMMON_RANGE_VALUE;
	AttakInveral = (int)(1 / (Data_->AttackInterval)*CCGlobleConfig::COMMON_ATTACKTIME_VALUE);
	MoveSpeed = Data_->MoveSpeed*CCGlobleConfig::COMMON_VALUE;
	CCLOG("MoveSpeed===  %d, attackRange === %f ,AttackInveral===%d ", MoveSpeed, AttakRange, AttakInveral);
	init_AttackInveral = Data_->AttackInterval;
	Init_AttackRange = AttakRange;
	Init_MoveSpeed = MoveSpeed;
	InitObj();
	AttackDamage = Data_->Attack*level;
	CurBlood = Data_->Blood*level;
	CCLOG("CurBlood ==%.0f ", CurBlood);
	MaxBlood = CurBlood;
	MaxSkillFrame = SKillData_->CoolTime * 60;

}


CSolider::~CSolider()
{
}
void CSolider::OnResourceLoadComplete()
{
	Obj->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	Obj->setPosition(Init_x, Init_y);
	Obj->setScale(Data_->ScaleValue);
	//Sprite* node = Sprite::createWithSpriteFrameName("player1.png");
	//node->setScale(0.5);
	//Sprite* node1 = Sprite::createWithSpriteFrameName("player1.png");
	//node1->setScale(0.5);
	//Sprite* node2 = Sprite::createWithSpriteFrameName("player1.png");
	//node2->setScale(0.5);
	//Sprite* node3 = Sprite::createWithSpriteFrameName("player1.png");
	//Sprite* node4 = Sprite::createWithSpriteFrameName("player1.png");
	//node3->setScale(0.5);
	//node4->setScale(0.5);
	UpPoint_ = Obj->getChildByName("buff1");
	BasePoint_ = Obj->getChildByName("basepoint");
	CenterPoint_ = Obj->getChildByName("centerpoint");
	LeftPoint_ = Obj->getChildByName("buff2");
	RightPoint_ = Obj->getChildByName("buff3");
	BulletPoint_ = getBulletPoint(Obj, "bulletpoint");
	/*BasePoint_->addChild(node1);
	UpPoint_->addChild(node);
	CenterPoint_->addChild(node2);
	LeftPoint_->addChild(node3);
	RightPoint_->addChild(node4);*/
	if (BulletPoint_ != nullptr)
	{
		if (Data_->ID == 2001)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node2 = node1->getChildByName("wuqi");
			BulletPos_ = node2->getPosition() + node1->getPosition() + node->getPosition();
		}
		else if (Data_->ID == 2002)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node2 = node1->getChildByName("wuqi");
			BulletPos_ = node2->getPosition() + node1->getPosition() + node->getPosition();
		}
		else if (Data_->ID == 2003)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node2 = node1->getChildByName("shou1");
			BulletPos_ = node2->getPosition() + node1->getPosition() + node->getPosition();
		}
		else if (Data_->ID == 3001)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node11 = node1->getChildByName("Sprite_24");
			Node*node2 = node11->getChildByName("wuqi");
			BulletPos_ = node2->getPosition() + node1->getPosition() + node11->getPosition() + node->getPosition();
		}
		else if (Data_->ID == 3002)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node2 = node1->getChildByName("Sprite_5");
			BulletPos_ = node2->getPosition() + node1->getPosition() + node->getPosition();
		}
		else if (Data_->ID == 3003)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node2 = node1->getChildByName("wuqi");
			BulletPos_ = node2->getPosition() + node1->getPosition() + node->getPosition();
		}
	}
	if (Ranks != 1)
	{
		Obj->setRotationSkewY(180);
		BulletPos_.x = -BulletPos_.x;
	}
	OnRun();
	

}
float  CSolider::GetBulletPointToBulletX()
{
	if (Ranks == 1)
	{
		return BulletPos_.x + BulletPoint_->getPositionX() + Obj->getPositionX();
	}
	else
	{
		return BulletPos_.x - BulletPoint_->getPositionX() + Obj->getPositionX();
	}

}
float  CSolider::GetBulletPointToBulletY()
{
	return BulletPos_.y + BulletPoint_->getPositionY() + Obj->getPositionY();
}
Vec2 CSolider::UpdateBulletPosition()
{
	if (Ranks == 1)
	{
		if (Data_->ID == 3001)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node11 = node1->getChildByName("Sprite_24");
			Node*node2 = node11->getChildByName("wuqi");
			return Vec2(2,-50)+ node2->getPosition() + node1->getPosition() + node11->getPosition() + node->getPosition() + BulletPoint_->getPosition() + Obj->getPosition();
		}
	}
	else
	{
		if (Data_->ID == 3001)
		{
			Node* node = Obj->getChildByName("bottom");
			Node*node1 = node->getChildByName("Node");
			Node*node11 = node1->getChildByName("Sprite_24");
			Node*node2 = node11->getChildByName("wuqi");
			int x = node2->getPositionX() + node1->getPositionX() + node11->getPositionX() + node->getPositionX() + BulletPoint_->getPositionX();
			int y = node2->getPositionY() + node1->getPositionY() + node11->getPositionY() + node->getPositionY() + BulletPoint_->getPositionY();
			return Vec2(-x+2+Obj->getPositionX(),-50+y+Obj->getPositionY());
		}
	}
	return Vec2::ZERO;
}

Node* CSolider::getBulletPoint(Node* node, std::string name)
{
	Vector<Node*> list = node->getChildren();
	for (Node* item : list)
	{
		if (item->getName().c_str() == name)
		{
			return item;
		}
		else
		{
			Node* temp = getBulletPoint(item, name);
			if (temp != nullptr&&temp->getName().c_str() == name)
			{
				return temp;
			}
		}
	}
	return nullptr;
}
void CSolider::Update()
{
	if (IsDelete_ == true)
		return;
	CBattleObject::Update();
	switch (OpreateType)
	{
	case ESoliderOpreate_Idle:
		AttackNum++;
		NowTime = CCGlobleConfig::GetCurrntTime();
		//CCLOG("Data.ID===%d  AttackInveral === %d", Data_->ID, AttakInveral);
		if (NowTime > LastAttackTime + AttakInveral)
		{
			LastAttackTime = NowTime;
			if (CheckAttackOrSkill() == false)
			{

			}
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
		AttackNum++;
		if (Ranks == 1)
			Obj->setPosition(Obj->getPosition().x + MoveSpeed, Obj->getPosition().y);
		else
			Obj->setPosition(Obj->getPosition().x - MoveSpeed, Obj->getPosition().y);
		if (AttackTarget != nullptr)
		{
			if (CheckAttackOrSkill() == false)
			{
				CheckEnemyInRange();
			}
			else
			{
				NowTime = CCGlobleConfig::GetCurrntTime();
				LastAttackTime = NowTime;
			}

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
	CBaseBoss* Sol = CBattleObjectManager::GetInstance()->GetEnemyByRange((float)Ranks, AttackData_->TargetType, (float)AttakRange, (float)RangeR_, (float)Obj->getPosition().x, (float)Obj->getPosition().y);
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
bool CSolider::CheckAttackOrSkill()
{
	if (AttackTarget == nullptr || AttackTarget->IsDelete_ == true)
	{
		AttackTarget = nullptr;
		OnRun();
		OpreateType = ESoliderOpreate_Walk;
		return false;
	}
	if (AttackNum >= MaxSkillFrame)
	{
		AttackNum = 0;
		OnSkill();
	}
	else
	{
		OnAttack();
	}
	CheckEnemyInRange();
	return true;
	//OnSkill();
}
void CSolider::OnIdle()
{
	OpreateType = ESoliderOpreate_Idle;
	CBattleObject::OnIdle();
}
void CSolider::OnRun()
{
	OpreateType = ESoliderOpreate_Walk;
	CBattleObject::OnRun();
}
void CSolider::OnAttack()
{
	CAttackManager::GetInstance()->OnAttack(this, AttackData_);
	OpreateType = ESoliderOpreate_Attack;
	CBattleObject::OnAttack();
}
void CSolider::OnHurt()
{
	OpreateType = ESoliderOpreate_Hurt;
	CBattleObject::OnHurt();
}
void  CSolider::GetBuff(CBuffData* data)
{
	if (data->Damage != 0)
	{
		GetDamage(data->Damage, 3);
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
void CSolider::GetDamage(int damage, int type)
{

	CCLOG("Damange:   %d , CurBlood = %.0f , MaxBlood = %.0f", damage, CurBlood, MaxBlood);
	damage = damage - damage*AttackCf;
	if (damage == 0)
		return;
	bool flag = (CurBlood <= MaxBlood*0.3f);
	CurBlood -= damage;
	isShowHurt = true;
	lastShowHurtTime = CCGlobleConfig::Game_time;

	if (CurBlood > 0 && CurBlood <= MaxBlood*0.3f)
	{
		CHurtShow *hurt = new CHurtShow();
		hurt->SetFont(3);
		hurt->ShowLabel(damage, this);
		CBattleObjectManager::GetInstance()->AddHurtShowObject(hurt);
		if (flag == false)
		{
			OnHurt();

		}
	}
	else if (CurBlood <= 0)
	{
		CSoliderDie* die = new CSoliderDie();
		die->ShowLabel(Ranks, this);
		CBattleObjectManager::GetInstance()->AddSoliderDie(die);
		CHurtShow *hurt = new CHurtShow();
		hurt->SetFont(3);
		hurt->ShowLabel(damage, this);
		CBattleObjectManager::GetInstance()->AddHurtShowObject(hurt);
		IsDelete_ = true;
		Obj->setVisible(false);
	}
	else
	{
		CHurtShow *hurt = new CHurtShow();
		hurt->SetFont(3);
		hurt->ShowLabel(damage, this);
		CBattleObjectManager::GetInstance()->AddHurtShowObject(hurt);
	}

}
void CSolider::GetMoveSpeedCf(float cf)
{
	MoveSpeedCf += cf;
	MoveSpeed = Init_MoveSpeed + Init_MoveSpeed*MoveSpeedCf;
	if (MoveSpeed <= 0)
		MoveSpeed = 0;
}
void CSolider::GetAttackSpeedCf(float cf)
{
	AttakInveralCf += cf;
	float temp = init_AttackInveral + init_AttackInveral *AttakInveralCf;
	AttakInveral = (int)(1 / temp*CCGlobleConfig::COMMON_ATTACKTIME_VALUE);
	if (AttakInveral < 0)
	{
		AttakInveral = 10000000;
	}
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
	CBattleObject::OnSkill();
}
