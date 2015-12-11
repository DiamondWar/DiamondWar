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
	//// ѡ�����ͣ������ͻ���ʱ����
	//Progress_->setType(kCCProgressTimerTypeRadial);
	//Progress_->setMidpoint(Point(0, 0));
	//Progress_->setBarChangeRate(Point(0, 1));
	//addChild(Progress_);
}
void CShuiJingBase::update(float dt)
{
	//CCProgressTimer *ct = (CCProgressTimer*)getChildByTag(10);
	//// ��ȡ��ǰ����
	//int num = ct->getPercentage();
	//// ���ý����ٶȣ��˴�Ϊÿ֡+1��
	//ct->setPercentage(++num);
	//// ������ѭ������
	//if (num >= 100)
	//	ct->setPercentage(0);
}