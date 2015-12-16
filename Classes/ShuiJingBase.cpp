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
	// ѡ�����ͣ������ͻ���ʱ����
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
		// ��ȡ��ǰ����
		int num = ct->getPercentage();
		// ���ý����ٶȣ��˴�Ϊÿ֡+1
		if (CoolTime % 3 == 0)
		{
			ct->setPercentage(--num);
		}
		CoolTime++;
		CCString* ns = CCString::createWithFormat("%d", (MaxCoolTime - CoolTime) / 60 + 1);
		CoolTimeLabel_->setString(ns->getCString());
		// ������ѭ������
		if (num <= 0)
		{
			IsLoading = false;//��ȴ�ɹ�
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

