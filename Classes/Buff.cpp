#include "Buff.h"
#include "CGlobleConfig.h"
USING_NS_CC;
CBuff::CBuff(CBuffData *data)
{
	BuffData = data;
	ResourceName = data->ResourceName+"1.png";
	DownLoadType = 2;
	InitObj();
}

void CBuff::OnResourceLoadComplete()
{
	Animation* animation = NULL;
	animation = AnimationCache::sharedAnimationCache()->getAnimation(BuffData->ResourceName);
	if (animation == NULL)
	{
		Vector<SpriteFrame*> vsp;
		for (int i = 1; i <= 4; i++)
		{
			String *string = String::createWithFormat("%s%d.png", BuffData->ResourceName, i);
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
			vsp.pushBack(spfr);
		}

		animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10.0f);
		AnimationCache::sharedAnimationCache()->addAnimation(animation, BuffData->ResourceName);

		Animate *animate = Animate::create(animation);
		auto *ac1 = RepeatForever::create(animate);
		this->runAction(ac1);
	}
	else
	{
		Animate *animate = Animate::create(animation);
		auto *ac1 = RepeatForever::create(animate);
		this->runAction(ac1);
	}

	if (BuffData->AttackType == 1||BuffData->AttackType== 3)
	{
		Obj->setPosition(BuffData->init_x, BuffData->init_y);
		BuffData->From->getParent()->addChild(Obj);
	}
	else
	{
		Obj->setPosition(0,0);
		BuffData->Target->Obj->addChild(Obj);
	}
	StartTime = CCGlobleConfig::GetCurrntTime();

}
void CBuff::Update()
{
	NowTime = CCGlobleConfig::GetCurrntTime();
	if (NowTime > StartTime + BuffData->ContinueTime)
	{
		//buf消失
		Obj->setVisible(false);
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

}
void CBuff::OnSkillActionComplete()
{

}
CBuff::~CBuff()
{
	
	Obj->release();
}
