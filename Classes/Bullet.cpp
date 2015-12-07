#include "Bullet.h"
#include "BattleObject.h"
#include "CGlobleConfig.h"
#include "ESystemEnum.h"
#include "Buff.h"
#include "BattleObjectManager.h"
CBullet::CBullet(CSkillData* data, int x, int y, CBuffData*  damage, CSolider* target, int rank, int type)
{
	Data_ = data;
	ResourceName = Data_->ResourceName + "_0.png";
	DownLoadType = type;
	Init_x = x;
	Init_y = y;
	AtTarget_ = target;
	Ranks_ = rank;
	RangeR_ = 10;
	iSpeed_ = Data_->BulletValue[1];
	BuffData = damage;
	InitObj();
}


CBullet::~CBullet()
{

}
void CBullet::OnResourceLoadComplete()
{
	float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, AtTarget_->Obj->getPosition().x, AtTarget_->Obj->getPosition().y);
	angle = angle * 180 / PI;
	Obj->setPosition(Init_x, Init_y);
}
//动作播放完成
void CBullet::OnHurtActionComplete()
{

}
void CBullet::OnAttackActionComplete()
{

}
void CBullet::OnSkillActionComplete()
{

}
void CBullet::Update()
{
	__super::Update();
	if (IsDelete_ == true)
		return;
	if (CheckIsAtTarget() == false)
	{
		float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, AtTarget_->Obj->getPosition().x, AtTarget_->Obj->getPosition().y);
		CCLOG("angle  huduzhizhi  === %f", angle);
		if (Ranks_ == 1)
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
		else
		{
			if (angle >= 0)
			{
				Obj->setPosition(Obj->getPosition().x - iSpeed_*cos(angle), Obj->getPosition().y - iSpeed_*sin(angle));
			}
			else
			{
				Obj->setPosition(Obj->getPosition().x + iSpeed_*cos(angle), Obj->getPosition().y + iSpeed_*sin(angle));
			}
			
		}
			
		angle = angle * 180 / PI;
		CCLOG("angle jiaoduzhi === %f", angle);
		Obj->setRotation(-angle);
		if (Ranks_ != 1)
		{
			if (angle>=0)
				Obj->setRotationSkewY(180 - angle);
			else 
				Obj->setRotationSkewY(- angle);

		}
		else
		{
			if (angle < 0)
				Obj->setRotationSkewY(180 - angle);

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
bool CBullet::CheckIsAtTarget()
{
	if (Obj == nullptr)
		return true;
	float length = CCGlobleConfig::GetLengthByPoint(AtTarget_->Obj->getPosition().x, AtTarget_->Obj->getPosition().y, Obj->getPosition().x, Obj->getPosition().y);
	if (length-AtTarget_->RangeR_ <= iSpeed_)
	{
		return true;
	}
	return false;
}