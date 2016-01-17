#include "BaseBoss.h"
#include "Buff.h"
#include "BattleObjectManager.h"
#include "GameSceneControl.h"
#include "AudioManager.h"
USING_NS_CC;
CBaseBoss::CBaseBoss()
{}
CBaseBoss::CBaseBoss(int rank)
{
	DownLoadType = 1;
	if (rank == 1)
	{
		ResourceName = "Boss";
		Init_x = 150;
	}
	else
	{
		ResourceName = "Boss";
		Init_x = 1800;
	}
	Ranks = rank;
	Init_y = 480;
	CurBlood =10000;
	MaxBlood = 10000;
	RangeR_ = 80;
	InitObj();

}
void CBaseBoss::GetDamage(int damage, int type)
{
	CCLOG("Damange:   %d , CurBlood = %.0f , MaxBlood = %.0f", damage, CurBlood, MaxBlood);
	if (damage == 0)
		return;
	bool flag = CurBlood == 0;
	bool flag1 = CurBlood <= MaxBlood*0.3;
	bool flag2 = CurBlood <= MaxBlood*0.5;
	CurBlood -= damage;
	if (CurBlood <= 0)
	{
		CurBlood = 0;
		if (flag == false)
		{
			if (Ranks == 1)
			{
				CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(8, 3);
			}
			else
			{
				CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(4, 1.5);
			}
			CBuffData* data_ = new   CBuffData();
			data_->attackPoint = 3;
			data_->AttackType = 3;
			data_->ContinueTime = 0;
			data_->From = this;
			data_->Target = this;
			data_->init_x = BasePoint_->getPositionX() + Obj->getPositionX();
			data_->init_y = BasePoint_->getPositionY() + Obj->getPositionY();
			data_->ResourceFrameCount = 5;
			data_->ResourceName = "bossdie";
			CBuff*buff = new CBuff(data_);
			CBattleObjectManager::GetInstance()->AddBuffObject(buff);
			Obj->setVisible(false);
			CGameSceneControl::GetInstance()->AddScreenShake();
			
			if (Ranks == 1)
			{
				CCGlobleConfig::IsWinGame_ = false;
				CGameSceneControl::GetInstance()->OnScreenScale();
			}
				
			else
			{
				CCGlobleConfig::IsWinGame_ = true;
				CGameSceneControl::GetInstance()->OnScreenScale(-1520);
			}
				
			CAudioManager::GetInstance()->PlayerVoice("audio_bossdie");
		}
	}
	else if (CurBlood <= MaxBlood*0.3)
	{
		if (Ranks == 1)
		{
			if (flag1 == false)
			{
				CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(7, 2.5);
			}
			SpriteFrame* fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("myboss_3.png");
			BossSprite_->setSpriteFrame(fram);
		}
		else
		{

			SpriteFrame* fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemyboss_3.png");
			BossSprite_->setSpriteFrame(fram);
		}

	}
	else if (CurBlood <= MaxBlood*0.5)
	{
		if (Ranks == 1)
		{
			if (flag2 == false)
			{
				CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(7, 2.5);
			}
			SpriteFrame* fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("myboss_2.png");
			BossSprite_->setSpriteFrame(fram);
		}
		else
		{
			SpriteFrame* fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemyboss_2.png");
			BossSprite_->setSpriteFrame(fram);
		}
	}
	CHurtShow *hurt = new CHurtShow();
	hurt->SetFont(3);
	hurt->ShowLabel(damage, this);
	CBattleObjectManager::GetInstance()->AddHurtShowObject(hurt);

}
void CBaseBoss::GetBuff(CBuffData* data)
{

}
void CBaseBoss::GetMoveSpeedCf(float cf)
{

}
void CBaseBoss::GetAttackSpeedCf(float cf)
{

}
void  CBaseBoss::GetAttackRangeCf(float cf)
{

}
void CBaseBoss::GetAttackCf(float cf)
{
}
Vec2 CBaseBoss::UpdateBulletPosition()
{
	return Vec2::ZERO;
}
void CBaseBoss::OnResourceLoadComplete()
{
	BossSprite_ = static_cast<Sprite*>(Obj->getChildByName("Sprite"));
	if (Ranks == 1)
	{
		SpriteFrame* fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("myboss_1.png");
		BossSprite_->setSpriteFrame(fram);
	}
	else
	{
		SpriteFrame* fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemyboss_1.png");
		BossSprite_->setSpriteFrame(fram);
	}
	Obj->setAnchorPoint(ccp(0.5, 0.5));
	Obj->setPosition(Init_x, Init_y);
	UpPoint_ = Obj->getChildByName("buff1");
	BasePoint_ = Obj->getChildByName("basepoint");
	CenterPoint_ = Obj->getChildByName("centerpoint");
	LeftPoint_ = Obj->getChildByName("buff2");
	RightPoint_ = Obj->getChildByName("buff3");
	BulletPoint_ = Obj->getChildByName("bulletpoint");
	/*Sprite* node = Sprite::createWithSpriteFrameName("player1.png");
	node->setScale(0.5);
	Sprite* node1 = Sprite::createWithSpriteFrameName("player1.png");
	node1->setScale(0.5);
	Sprite* node2 = Sprite::createWithSpriteFrameName("player1.png");
	node2->setScale(0.5);
	Sprite* node3 = Sprite::createWithSpriteFrameName("player1.png");
	Sprite* node4 = Sprite::createWithSpriteFrameName("player1.png");
	node3->setScale(0.5);
	node4->setScale(0.5);
	BasePoint_->addChild(node1);
	UpPoint_->addChild(node);
	CenterPoint_->addChild(node2);
	LeftPoint_->addChild(node3);
	RightPoint_->addChild(node4);*/

}
void CBaseBoss::OnHurtActionComplete()
{

}
void CBaseBoss::OnAttackActionComplete()
{

}
void CBaseBoss::OnSkillActionComplete()
{

}
void CBaseBoss::Update()
{
	CBattleObject::Update();
}
void CBaseBoss::OnIdle()
{
	CBattleObject::OnIdle();
}
void CBaseBoss::OnRun()
{
	CBattleObject::OnRun();
}
void CBaseBoss::OnAttack()
{
	CBattleObject::OnAttack();
}
void CBaseBoss::OnSkill()
{
	CBattleObject::OnSkill();
}
void CBaseBoss::OnHurt()
{
	CBattleObject::OnHurt();
}
CBaseBoss::~CBaseBoss()
{
}
