#include "ShuiJingBase.h"
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
	String* string = String::createWithFormat("shujing_%d.png", index);
	MainSprite_ = CCSprite::createWithSpriteFrameName(string->getCString());
	MainSprite_->setAnchorPoint(Vec2(0, 0));
	addChild(MainSprite_);
	//Progress_ = ProgressTimer::create(MainSprite_);
	//Progress_->setPercentage(0);
	//Progress_->setTag(10);
	//// 选择类型，是条型还是时针型
	//Progress_->setType(kCCProgressTimerTypeRadial);
	//Progress_->setMidpoint(Point(0, 0));
	//Progress_->setBarChangeRate(Point(0, 1));
	//addChild(Progress_);
}
void CShuiJingBase::update(float dt)
{
	//CCProgressTimer *ct = (CCProgressTimer*)getChildByTag(10);
	//// 获取当前进度
	//int num = ct->getPercentage();
	//// 设置进度速度（此处为每帧+1）
	//ct->setPercentage(++num);
	//// 设置了循环播放
	//if (num >= 100)
	//	ct->setPercentage(0);
}