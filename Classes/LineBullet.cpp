#include "LineBullet.h"
#include "CGlobleConfig.h"
#include "ESystemEnum.h"
#include "Buff.h"
#include "BattleObjectManager.h"
USING_NS_CC;
CLineBullet::CLineBullet(CAttackData* data, int x, int y, CBuffData*  damage, CSolider* target, int rank, int type)
{
	Data_ = data;
	ResourceName = data->ResourceName1 + "_1.png";
	FrameCount = data->ResourceFrameCount1;
	DownLoadType = type;
	Init_x = x;
	Init_y = y;
	LineLength = data->BulletValue[2];
	AtTarget_ = target;
	if (Data_->AttackPoint == 1)
	{
		TargetNode = target->CenterPoint_;
	}
	else if (data->AttackPoint == 2)
	{
		TargetNode = target->UpPoint_;
	}
	else if (data->AttackPoint == 3)
	{
		TargetNode = target->BasePoint_;
	}
	else if (data->AttackPoint == 4)
	{
		TargetNode = target->LeftPoint_;
	}
	else if (data->AttackPoint == 5)
	{
		TargetNode = target->RightPoint_;
	}

	Ranks_ = rank;
	RangeR_ = 10;
	iSpeed_ = Data_->BulletValue[1] * CCGlobleConfig::COMMON_BULLESPEED_VALUE;
	BuffData = damage;

	InitObj();
}


CLineBullet::~CLineBullet()
{

}
void CLineBullet::OnResourceLoadComplete()
{
	float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, TargetNode->getPosition().x + AtTarget_->Obj->getPosition().x, TargetNode->getPosition().y + AtTarget_->Obj->getPosition().y);
	angle = angle * 180 / PI;
	Obj->setPosition(Init_x, Init_y);

	Animation* animation = NULL;
	animation = AnimationCache::sharedAnimationCache()->getAnimation(Data_->ResourceName1);
	if (animation == NULL)
	{
		Vector<SpriteFrame*> vsp;
		for (int i = 1; i <= FrameCount; i++)
		{
			String *string = String::createWithFormat("%s_%d.png", Data_->ResourceName1.data(), i);
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
			vsp.pushBack(spfr);
		}

		animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
		AnimationCache::sharedAnimationCache()->addAnimation(animation, ResourceName);
	}
	Animate *animate = Animate::create(animation);
	auto *ac1 = RepeatForever::create(animate);
	Obj->runAction(ac1);
}
//动作播放完成
void CLineBullet::OnHurtActionComplete()
{

}
void CLineBullet::OnAttackActionComplete()
{

}
void CLineBullet::OnSkillActionComplete()
{

}
void CLineBullet::Update()
{
	
	if (IsDelete_ == true)
		return;
	CBattleObject::Update();
	if (CheckIsAtTarget() == false)
	{
		float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, TargetNode->getPosition().x + AtTarget_->Obj->getPosition().x, TargetNode->getPosition().y + AtTarget_->Obj->getPosition().y);
		if (Ranks_ == 1)
		{
			if (angle >= 0)
			{
				Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(angle), Obj->getPosition().y + iSpeed_*sin(angle));
			}
			else
			{
				Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(angle), Obj->getPosition().y + iSpeed_*sin(angle));
			}
		}
		else
		{
			if (Obj->getPosition().x > AtTarget_->Obj->getPosition().x)
			{
				if (angle >= 0)
				{
					Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(angle), Obj->getPosition().y - iSpeed_*sin(angle));
				}
				else
				{
					Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(angle), Obj->getPosition().y - iSpeed_*sin(angle));
				}
			}
			else
			{
				if (angle >= 0)
				{
					Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(angle), Obj->getPosition().y + iSpeed_*sin(angle));

				}
				else
				{
					Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(angle), Obj->getPosition().y - iSpeed_*sin(angle));
				}
			}


		}

		angle = angle * 180 / PI;
		Obj->setRotation(-angle);
		if (Ranks_ != 1)
		{
			Obj->setRotationSkewY(180 - angle);

		}
		else
		{
			if (angle < 0)
				Obj->setRotationSkewY(-angle);

		}
	}
	else
	{
		IsDelete_ = true;
		Obj->setVisible(false);
		CBuff* buff = new CBuff(BuffData);
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}

}
bool CLineBullet::CheckIsAtTarget()
{
	if (Obj == nullptr)
		return true;
	float length = CCGlobleConfig::GetLengthByPoint(TargetNode->getPosition().x + AtTarget_->Obj->getPosition().x, TargetNode->getPosition().y + Obj->getPosition().y, Obj->getPosition().x, Obj->getPosition().y);
	if (length - AtTarget_->RangeR_ <= iSpeed_)
	{
		return true;
	}
	return false;
}