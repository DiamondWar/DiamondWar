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
	LineLength = data->BulletValue[2]*CCGlobleConfig::COMMON_RANGE_VALUE;
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
	RangeR_ = Data_->BulletValue[0];
	iSpeed_ = Data_->BulletValue[1] * CCGlobleConfig::COMMON_BULLESPEED_VALUE;
	BuffData = damage;
	InitObj();
}


CLineBullet::~CLineBullet()
{

}
void CLineBullet::OnResourceLoadComplete()
{
	Angle_ = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, TargetNode->getPosition().x + AtTarget_->Obj->getPosition().x, TargetNode->getPosition().y + AtTarget_->Obj->getPosition().y);
	 float angle = Angle_ * 180 / PI;
	Obj->setPosition(Init_x, Init_y);
	if (Angle_ != 0)
	{
		LineLength = abs(LineLength / cos(Angle_));
	}
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
		if (Ranks_ == 1)
		{
			if (Angle_ >= 0)
			{
				Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(Angle_), Obj->getPosition().y + iSpeed_*sin(Angle_));
			}
			else
			{
				Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(Angle_), Obj->getPosition().y + iSpeed_*sin(Angle_));
			}
		}
		else
		{
			if (Obj->getPosition().x > AtTarget_->Obj->getPosition().x)
			{
				if (Angle_ >= 0)
				{
					Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(Angle_), Obj->getPosition().y - iSpeed_*sin(Angle_));
				}
				else
				{
					Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(Angle_), Obj->getPosition().y - iSpeed_*sin(Angle_));
				}
			}
			else
			{
				if (Angle_ >= 0)
				{
					Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(Angle_), Obj->getPosition().y + iSpeed_*sin(Angle_));

				}
				else
				{
					Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(Angle_), Obj->getPosition().y - iSpeed_*sin(Angle_));
				}
			}
		}
		CCLOG("Obj.name ==%s   Pos ==%f,%f", Obj->getName().c_str(), Obj->getPositionX(), Obj->getPositionY());
		CheckEnemyInAttackRange();
	}
	else
	{
		IsDelete_ = true;
		Obj->setVisible(false);
		
	}

}
bool CLineBullet::CheckIsAtTarget()
{
	if (Obj == nullptr)
		return true;
	float length = CCGlobleConfig::GetLengthByPoint(Init_x, Init_y, Obj->getPosition().x, Obj->getPosition().y);
	CCLOG(" CLineBullet::CheckIsAtTarget ==%f, LineLength=%f", length, LineLength);
	if (length >= LineLength)
	{
		return true;
	}
	return false;
}
void CLineBullet::CheckEnemyInAttackRange()
{
	CSolider* solider = CBattleObjectManager::GetInstance()->GetEnemyByRange(Ranks_, 0, 0, Obj->getPosition().x, Obj->getPosition().y);
	if (LastTarget_ == solider||LastTarget_!=nullptr)
		return;
	LastTarget_ = solider;
	BuffData->Target = solider;
	CBuff* buff = new CBuff(BuffData);
	CBattleObjectManager::GetInstance()->AddBuffObject(buff);
}