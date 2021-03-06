#include "Buff.h"
#include "CGlobleConfig.h"
#include "BattleObjectManager.h"
#include "AudioManager.h"
#include "GameSceneControl.h"
USING_NS_CC;
CBuff::CBuff(CBuffData *data)
{
	BuffData = data;
	ResourceName = data->ResourceName + "_1.png";
	DownLoadType = 2;
	InitObj();
}

void CBuff::OnResourceLoadComplete()
{
	if (BuffData->ContinueTime == 0)
		GetResultHurt();
	else
	{
		if (BuffData->InveralTime == 0)
		{
			BuffData->Target->GetAttackCf(BuffData->Damage);
			BuffData->Target->GetAttackCf(BuffData->AttackCf);
			BuffData->Target->GetMoveSpeedCf(BuffData->SpeedCf);
			BuffData->Target->GetAttackRangeCf(BuffData->AttackRangeCf);
			BuffData->Target->GetAttackSpeedCf(BuffData->AttackInveralCf);
		}
	}
	if (Obj == nullptr)
	{
		return;
	}

	if (BuffData->AttackType == 2 || BuffData->AttackType == 3)
	{
		if (BuffData->attackPoint == 1)
		{
			Obj->setAnchorPoint(Vec2(0.5, 0.5));
		}
		else if (BuffData->attackPoint == 2)
		{
			Obj->setAnchorPoint(Vec2(0.5, 1));
		}
		else if (BuffData->attackPoint == 3)
		{
			Obj->setAnchorPoint(Vec2(0.5, 0));
		}
		else if (BuffData->attackPoint == 4)
		{
			Obj->setAnchorPoint(Vec2(1, 0.5));
		}
		else if (BuffData->attackPoint == 5)
		{
			Obj->setAnchorPoint(Vec2(0, 0.5));
		}
		else if (BuffData->attackPoint == 6)
		{
			Obj->setAnchorPoint(Vec2(0.5, 0.5));
		}
		Obj->setPosition(BuffData->init_x, BuffData->init_y);
		CGameSceneControl::GetInstance()->GameRoot_->addChild(Obj);
	}
	else
	{
		if (BuffData->attackPoint == 1)
		{
			Obj->setAnchorPoint(Vec2(0.5, 0.5));
			Obj->setPosition(BuffData->Target->CenterPoint_->getPosition());
			BuffData->Target->Obj->addChild(Obj);
		}
		else if (BuffData->attackPoint == 2)
		{
			BuffData->Target->Obj->addChild(Obj);
			Obj->setAnchorPoint(Vec2(0.5, 0.5));
			Obj->setPosition(BuffData->Target->UpPoint_->getPosition());
		}
		else if (BuffData->attackPoint == 3)
		{

			BuffData->Target->Obj->addChild(Obj);
			Obj->setAnchorPoint(Vec2(0.5, 0));
			Obj->setPosition(BuffData->Target->BasePoint_->getPosition());
		}
		else if (BuffData->attackPoint == 4)
		{

			BuffData->Target->Obj->addChild(Obj);
			Obj->setAnchorPoint(Vec2(1, 0.5));
			Obj->setPosition(BuffData->Target->LeftPoint_->getPosition());
		}
		else if (BuffData->attackPoint == 5)
		{

			BuffData->Target->Obj->addChild(Obj);
			Obj->setAnchorPoint(Vec2(0, 0.5));
			Obj->setPosition(BuffData->Target->RightPoint_->getPosition());
		}
		else if (BuffData->attackPoint == 6)
		{
			Obj->setAnchorPoint(Vec2(0.5, 0.5));
			BuffData->Target->BulletPoint_->addChild(Obj);
			
			
		}
	}
	StartTime = CCGlobleConfig::GetCurrntTime();
	Animation* animation = NULL;
	animation = AnimationCache::sharedAnimationCache()->getAnimation(BuffData->ResourceName);
	if (animation == NULL)
	{
		Vector<SpriteFrame*> vsp;
		for (int i = 1; i <= BuffData->ResourceFrameCount; i++)
		{
			String *string = String::createWithFormat("%s_%d.png", BuffData->ResourceName.data(), i);
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
			vsp.pushBack(spfr);
		}

		animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
		AnimationCache::sharedAnimationCache()->addAnimation(animation, BuffData->ResourceName);
	}
	Animate *animate = Animate::create(animation);
	if (BuffData->ContinueTime == 0)
	{
		CCCallFunc * funcall = CCCallFunc::create(this, callfunc_selector(CBuff::OnAttackActionComplete));
		CCFiniteTimeAction * seq = CCSequence::create(animate, funcall, NULL);
		Obj->runAction(seq);

	}
	else
	{
		auto *ac1 = RepeatForever::create(animate);
		Obj->runAction(ac1);
	}



}
void CBuff::Update()
{
	if (BuffData->Target == nullptr || BuffData->ContinueTime == 0)
		return;
	NowTime = CCGlobleConfig::GetCurrntTime();
	if (NowTime > StartTime + BuffData->ContinueTime*CCGlobleConfig::COMMON_ATTACKTIME_VALUE)
	{
		//buf消失
		OnAttackActionComplete();
	}
	else
	{
		if (BuffData->InveralTime > 0)
		{
			if (NowTime > LastTime + BuffData->InveralTime*CCGlobleConfig::COMMON_ATTACKTIME_VALUE)
			{
				//间隔时间到了 进行造成伤害
				LastTime = NowTime;
				BuffData->Target->GetAttackCf(BuffData->AttackCf);
				BuffData->Target->GetDamage(BuffData->Damage, 3);
				BuffData->Target->GetMoveSpeedCf(BuffData->SpeedCf);
				BuffData->Target->GetAttackRangeCf(BuffData->AttackRangeCf);
				BuffData->Target->GetAttackSpeedCf(BuffData->AttackInveralCf);
			}
		}
	}
}
//动作播放完成
void CBuff::OnHurtActionComplete()
{

}
void CBuff::OnAttackActionComplete()
{
	if (BuffData->Target != nullptr)
	{
		BuffData->Target->GetAttackCf(-BuffData->AttackCf);
		BuffData->Target->GetMoveSpeedCf(-BuffData->SpeedCf);
		BuffData->Target->GetAttackRangeCf(-BuffData->AttackRangeCf);
		BuffData->Target->GetAttackSpeedCf(-BuffData->AttackInveralCf);
	}
	if (BuffData->ResourceName == "bossdie")
	{
		CCGlobleConfig::IsEndGame_ = true;
	}
	
	if (Obj!=nullptr)
		Obj->setVisible(false);
	IsDelete_ = true;
}
void CBuff::OnSkillActionComplete()
{

}
void CBuff::GetResultHurt()
{
	CAudioManager::GetInstance()->PlayerVoice(BuffData->HitVoice_);
	//造成一次伤害的走这里
	if (BuffData->NextBuff == NULL)
	{
		if (BuffData->Target != NULL)
		{
			BuffData->Target->GetDamage(BuffData->Damage,3);
		}
	}
	else
	{
		CCLOG("xiayige  buff");
		
		CBuff* buff = new CBuff(BuffData->NextBuff);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}
}
CBuff::~CBuff()
{
	if (Obj != nullptr)
		Obj->release();
}
