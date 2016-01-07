#include "SpellLiuXingBullet.h"
#include "CGlobleConfig.h"
#include "Buff.h"
#include "BattleObjectManager.h"
#include "GameSceneControl.h"
USING_NS_CC;
CSpellLiuXingBullet::CSpellLiuXingBullet(CAttackData* data, int x, int y, CBuffData* damage,int length, int rank, int type)
{
	Data_ = data;
	ResourceName = data->ResourceName1 + "_1.png";
	FrameCount = data->ResourceFrameCount1;
	DownLoadType = type;
	Init_x = x;
	Init_y = y;
	if (rank == 1)
		Target_x = x + length;
	else
		Target_x = x - length;

	Target_y = y - length;
	
	Ranks_ = rank;
	RangeR_ = 10;
	iSpeed_ = Data_->BulletValue[1] * CCGlobleConfig::COMMON_BULLESPEED_VALUE;
	BuffData = damage;

	InitObj();
}


CSpellLiuXingBullet::~CSpellLiuXingBullet()
{

}
void CSpellLiuXingBullet::OnResourceLoadComplete()
{
	float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, Target_x, Target_y);
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
void CSpellLiuXingBullet::OnHurtActionComplete()
{

}
void CSpellLiuXingBullet::OnAttackActionComplete()
{

}
void CSpellLiuXingBullet::OnSkillActionComplete()
{

}
void CSpellLiuXingBullet::Update()
{
	CBattleObject::Update();
	if (IsDelete_ == true)
		return;
	if (CheckIsAtTarget() == false)
	{
		float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, Target_x, Target_y);
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
			if (Obj->getPosition().x > Target_x)
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
		Obj->setRotation(-90-angle);
		if (Ranks_ != 1)
		{
			Obj->setRotationSkewY(-90+180 - angle);

		}
		else
		{
			if (angle < 0)
				Obj->setRotationSkewY(-90-angle);

		}
	}
	else
	{
		IsDelete_ = true;
		Obj->setVisible(false);
		CBuff* buff = new CBuff(BuffData);
		BuffData->attackPoint =2;
		BuffData->init_x =Target_x;
		BuffData->init_y = Target_y;
		CBattleObjectManager::GetInstance()->AddBuffObject(buff);
	}

}
bool CSpellLiuXingBullet::CheckIsAtTarget()
{
	if (Obj == nullptr)
		return true;
	float length = CCGlobleConfig::getLengthByCircle(Target_x, Target_y, Obj->getPosition().x, Obj->getPosition().y);
	if (length-50 <= iSpeed_)
	{
		return true;
	}
	return false;
}