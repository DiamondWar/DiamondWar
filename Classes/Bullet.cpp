#include "Bullet.h"
#include "BattleObject.h"
#include "CGlobleConfig.h"

CBullet::CBullet(int id, std::string resourename,cocos2d::Vec2 position,CSolider* target,int rank, int type)
{
	ResourceName = resourename;
	DownLoadType = type;
	InitObj();
	Init_x = position.x;
	Init_y = position.y;
	AtTarget_ = target;
	Ranks_ = rank;
	RangeR_ = 10;
}


CBullet::~CBullet()
{

}
void CBullet::OnResourceLoadComplete()
{
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
	/*if (CheckIsAtTarget() == false)
	{
	if (Ranks_ == 1)
	Obj->setPosition(Obj->getPosition().x + iSpeed_, Obj->getPosition().y);
	else
	Obj->setPosition(Obj->getPosition().x - iSpeed_, Obj->getPosition().y);
	}
	else
	{
	IsDelete_ = false;
	Obj->setVisible(false);
	}*/
	
}
bool CBullet::CheckIsAtTarget()
{
	float length = CCGlobleConfig::GetLengthByPoint(AtTarget_->Obj->getPosition().x, AtTarget_->Obj->getPosition().y, Obj->getPosition().x, Obj->getPosition().y);
	if (length <= 5)
	{
		return true;
	}
	return false;
}