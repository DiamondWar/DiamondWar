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
void CShuiJingBase::SetInfo(int index)
{
	MyColor = index;
	String* string = String::createWithFormat("shujing_%d.png", index);
	MainSprite_ = CCSprite::createWithSpriteFrameName(string->getCString());
	MainSprite_->setAnchorPoint(Vec2(0, 0));
	addChild(MainSprite_);

	Sprite* sprite = CCSprite::createWithSpriteFrameName("shujing_0.png");
	Progress_ = ProgressTimer::create(sprite);
	Progress_->setPercentage(0);
	Progress_->setTag(10);
	// 选择类型，是条型还是时针型
	Progress_->setType(kCCProgressTimerTypeRadial);
	Progress_->setAnchorPoint(Vec2(0, 0));
	Progress_->setReverseProgress(true);
	addChild(Progress_);

	TTFConfig config("fonts/ERASDEMI.TTF", 80);
	CoolTimeLabel_ = Label::createWithTTF(config, "", TextHAlignment::LEFT);
	CoolTimeLabel_->setAnchorPoint(Vec2(0.5, 0.5));
	CoolTimeLabel_->setPosition(55, 75);
	CoolTimeLabel_->setTextColor(Color4B::RED);
	addChild(CoolTimeLabel_);

}
void CShuiJingBase::update(float dt)
{
	if (IsLoading == true)
	{
		CCProgressTimer *ct = (CCProgressTimer*)getChildByTag(10);
		// 获取当前进度
		int num = ct->getPercentage();
		// 设置进度速度（此处为每帧+1
		if (CoolTime % 3 == 0)
		{
			ct->setPercentage(--num);
		}
		CoolTime++;
		CCString* ns = CCString::createWithFormat("%d", (MaxCoolTime - CoolTime) / 60 + 1);
		CoolTimeLabel_->setString(ns->getCString());
		// 设置了循环播放
		if (num <= 0)
		{
			IsLoading = false;//冷却成功
			CoolTimeLabel_->setString("");
		}
	}
	else
	{
		CoolTime = 0;
	}

}
void CShuiJingBase::ResetInfo(int Color,bool flag )
{
	MyColor = Color;
	String* string = String::createWithFormat("shujing_%d.png", Color);
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
	MainSprite_->setSpriteFrame(frame);

	if (flag == false)
	Progress_->setPercentage(0);
	else 
		Progress_->setPercentage(100);
	IsLoading = flag;
}

