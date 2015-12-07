#include "Buff.h"
#include "CGlobleConfig.h"
#include "BattleObjectManager.h"
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
	if (Obj == nullptr)
	{

		return;
	}
	if (BuffData->AttackType == 2 || BuffData->AttackType == 3)
	{
		Obj->setPosition(BuffData->init_x, BuffData->init_y);
		BuffData->From->getParent()->addChild(Obj);
	}
	else
	{
		Obj->setPosition(0, 0);
		BuffData->Target->Obj->addChild(Obj);
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
			CCLOG("------------%s", string->getCString());
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
			vsp.pushBack(spfr);
		}
		
		animation = Animation::createWithSpriteFrames(vsp,1.0f/10);
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
	if (BuffData->ContinueTime == 0)
		return;
	NowTime = CCGlobleConfig::GetCurrntTime();
	if (NowTime > StartTime + BuffData->ContinueTime)
	{
		//buf消失
		Obj->setVisible(false);
		IsDelete_ = true;
		this->release();
	}
	else
	{
		if (NowTime > LastTime + BuffData->InveralTime)
		{
			//间隔时间到了 进行造成伤害
			LastTime = NowTime;

		}
	}
}
//动作播放完成
void CBuff::OnHurtActionComplete()
{

}
void CBuff::OnAttackActionComplete()
{
	Obj->setVisible(false);
	IsDelete_ = true;
	this->release();
}
void CBuff::OnSkillActionComplete()
{

}
void CBuff::GetResultHurt()
{
	//造成一次伤害的走这里
	if (BuffData->NextBuff == NULL)
	{
		if (BuffData->Target != NULL)
		{
			BuffData->Target->GetDamage(BuffData->Damage);
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
	if (Obj!= nullptr)
		Obj->release();
}
