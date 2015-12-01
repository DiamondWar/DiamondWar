#include "Bullet.h"
#include "BattleObject.h"
#include "CGlobleConfig.h"

CBullet::CBullet(int id, std::string resourename, int x, int y, int damage, CSolider* target, int rank, int type)
{
	ResourceName = resourename+"_0.png";
	DownLoadType = type;
	Init_x = x;
	Init_y = y;
	AtTarget_ = target;
	Ranks_ = rank;
	RangeR_ = 10;
	iSpeed_ = 10;
	Damage = damage;
	InitObj();
}


CBullet::~CBullet()
{

}
void CBullet::OnResourceLoadComplete()
{
	float angle = CCGlobleConfig::GetAngleByPoint(Init_x, Init_y, AtTarget_->Obj->getPosition().x, AtTarget_->Obj->getPosition().y);
	angle = angle * 180 / PI;
	CCLOG("angle === %f", angle);
	Obj->setPosition(Init_x, Init_y);

	/*if (Ranks_ != 1)
	{
	Obj->setRotationSkewY(180);

	}*/
	//Obj->setRotation(-060);


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

		if (Ranks_ == 1)
			Obj->setPosition(Obj->getPosition().x + iSpeed_*sin(angle), Obj->getPosition().y + iSpeed_*cos(angle));
		else
			Obj->setPosition(Obj->getPosition().x - iSpeed_*sin(angle), Obj->getPosition().y - iSpeed_*cos(angle));
		angle = angle * 180 / PI;
		Obj->setRotation(-angle);
		if (Ranks_ != 1)
		{
			Obj->setRotationSkewY(180 - angle);

		}
	}
	else
	{
		IsDelete_ = true;
		Obj->setVisible(false);
		AtTarget_->GetDamage(Damage);
	}

}
bool CBullet::CheckIsAtTarget()
{
	if (Obj == nullptr)
		return true;
	float length = CCGlobleConfig::GetLengthByPoint(AtTarget_->Obj->getPosition().x, AtTarget_->Obj->getPosition().y, Obj->getPosition().x, Obj->getPosition().y);
	
	CCLOG("Length == =%f  , RangR == %d", length,AtTarget_->RangeR_);

	if (length-AtTarget_->RangeR_ <= iSpeed_)
	{
		return true;
	}
	return false;
}