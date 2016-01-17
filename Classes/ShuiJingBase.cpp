#include "ShuiJingBase.h"
#include "CGlobleConfig.h"
USING_NS_CC;

bool CShuiJingBase::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->scheduleUpdate();
	return true;
}
void CShuiJingBase::SetInfo(int index, bool flag)
{
	IsCanLoading_ = true;
	IsLoading = false;
	IsCanChose_ = flag;
	MyColor = index;

	Sprite*bg = Sprite::createWithSpriteFrameName("shuijing_Bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	addChild(bg);
	String* st = String::createWithFormat("UI_crystal_shuijing_%d_1.png", index);
	AnimationSp_ = CCSprite::createWithSpriteFrameName(st->getCString());
	Animation* animation = NULL;
	String* st1 = String::createWithFormat("ShuiJing_%d", index);
	animation = AnimationCache::sharedAnimationCache()->getAnimation(st1->getCString());
	Animate *animate = Animate::create(animation);
	auto *ac1 = RepeatForever::create(animate);
	AnimationSp_->runAction(ac1);
	AnimationSp_->setVisible(false);
	String* string = String::createWithFormat("shuijing_%d.png", index);
	MainSprite_ = CCSprite::createWithSpriteFrameName(string->getCString());
	MainSprite_->setAnchorPoint(Vec2(0, 0));
	addChild(MainSprite_);

	Sprite* sprite = CCSprite::createWithSpriteFrameName("shuijing_0.png");
	Progress_ = ProgressTimer::create(sprite);
	Progress_->setPercentage(0);
	Progress_->setTag(10);
	// 选择类型，是条型还是时针型
	Progress_->setType(kCCProgressTimerTypeRadial);
	Progress_->setAnchorPoint(Vec2(0, 0));
	Progress_->setReverseProgress(true);
	AnimationSp_->setAnchorPoint(ccp(0, 0));
	addChild(AnimationSp_);
	addChild(Progress_);
	TimeSp_ = Sprite::createWithSpriteFrameName("shuijingshuzi_0.png");
	TimeSp_->setAnchorPoint(Vec2(0.5, 0.5));
	TimeSp_->setPosition(55, 75);
	TimeSp_->setVisible(false);
	addChild(TimeSp_);
	if (IsCanChose_ == false)
	{
		int num = Progress_->getPercentage();
		num = 100;
		Progress_->setPercentage(num);
		SetCanExist(false);
	}


}
void CShuiJingBase::SetCanExist(bool flag)
{
	//AnimationSp_->setVisible(flag);
	Progress_->setVisible(flag);
	MainSprite_->setVisible(flag);

}
void CShuiJingBase::SetShuiJingLoadComplete()
{
	IsCanLoading_ = true;
	IsLoading = false;
	Progress_->setPercentage(0);
	CurMaxCoolTime = MaxCoolTime;
	setVisible(true);
}
void CShuiJingBase::SetShuiJingCanLoading(int cooltime)
{
	CurMaxCoolTime = cooltime;
}
int CShuiJingBase::GetCurCoolTime()
{
	return CurMaxCoolTime;
}
void CShuiJingBase::update(float dt)
{
	if (IsLoading == true)
	{
		CCProgressTimer *ct = (CCProgressTimer*)getChildByTag(10);
		// 获取当前进度
		float num = ct->getPercentage();
		// 设置进度速度（此处为每帧+1
		if (CurMaxCoolTime < 100000)
			CurMaxCoolTime--;
		if (CurMaxCoolTime < 0)
			CurMaxCoolTime = 0;
		if (CurMaxCoolTime <= MaxCoolTime)
		{
			SetCanExist(true);
			TimeSp_->setVisible(true);
			num -= 100.0 / 180.0;
			ct->setPercentage(num);
			CCString* ns = CCString::createWithFormat("shuijingshuzi_%d.png", CurMaxCoolTime / 60 + 1);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(ns->getCString());
			TimeSp_->setSpriteFrame(frame);
		}
		else
		{
			SetCanExist(false);
			TimeSp_->setVisible(false);
		}

		// 设置了循环播放
		if (num <= 0)
		{
			CurMaxCoolTime = 0;
			IsLoading = false;//冷却成功
			TimeSp_->setVisible(false);
		}
	}
	else
	{
		CurMaxCoolTime = 0;
	}

}
void CShuiJingBase::ResetInfo(int num, int Color, bool flag)
{
	MyColor = Color;
	Animation* animation = NULL;
	String* st1 = String::createWithFormat("ShuiJing_%d", Color);
	animation = AnimationCache::sharedAnimationCache()->getAnimation(st1->getCString());
	if (animation != NULL)
	{
		Animate *animate = Animate::create(animation);
		auto *ac1 = RepeatForever::create(animate);
		AnimationSp_->stopAllActions();
		AnimationSp_->runAction(ac1);
		AnimationSp_->setVisible(false);
	}
	else
	{
		AnimationSp_->setVisible(false);
	}

	IsCanLoading_ = true;
	String* string = String::createWithFormat("shuijing_%d.png", Color);
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
	MainSprite_->setSpriteFrame(frame);

	if (flag == false)
		Progress_->setPercentage(0);
	else
	{
		Progress_->setPercentage(100);
		SetCanExist(false);
	}

	IsLoading = flag;

}
void CShuiJingBase::SetTipsInfo(bool flag)
{
	//添加光效显示
	IsTips_ = flag;
	if (flag == false)
	{
		AnimationSp_->setVisible(false);
	}
	else
	{
		AnimationSp_->setVisible(true);
	}
}
