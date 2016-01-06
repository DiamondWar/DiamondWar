#include "BaseBoss.h"
#include "Buff.h"
USING_NS_CC;
CBaseBoss::CBaseBoss()
{}
CBaseBoss::CBaseBoss(int rank)
{
	DownLoadType = 2;
	if (rank == 1)
	{
		ResourceName = "myboss.png";
		Init_x = 160;
	}
	else
	{
		ResourceName = "enemyboss.png";
		Init_x = 1750;
	}
	Init_y = 520;
	CurBlood = 10000;
	MaxBlood = 10000;
	InitObj();
	
}
void CBaseBoss::GetDamage(int damage, int type)
{
	CCLOG("Damange:   %d , CurBlood = %.0f , MaxBlood = %.0f", damage, CurBlood, MaxBlood);
	if (damage == 0)
		return;
	bool flag = (CurBlood <= MaxBlood*0.3f);
	CurBlood -= damage;
	if (CurBlood <= 0)
		CurBlood = 0;  
}
void CBaseBoss::GetBuff(CBuffData* data)
{

}
void CBaseBoss::GetMoveSpeedCf(float cf)
{

}
void CBaseBoss::GetAttackSpeedCf(float cf)
{

}
void  CBaseBoss::GetAttackRangeCf(float cf)
{

}
void CBaseBoss::GetAttackCf(float cf)
{
}
Vec2 CBaseBoss::UpdateBulletPosition()
{
	return Vec2::ZERO;
}
void CBaseBoss::OnResourceLoadComplete()
{
	
	Obj->setPosition(Init_x, Init_y);
	BasePoint_ = Node::create();
	BasePoint_->setPosition(0, 0);
	Obj->addChild(BasePoint_);
	CenterPoint_ = Node::create();
	CenterPoint_->setPosition(Obj->getContentSize().width / 2, Obj->getContentSize().height / 2);
	Obj->addChild(CenterPoint_);
	LeftPoint_ = Node::create();
	Obj->addChild(LeftPoint_);
	LeftPoint_->setPosition(0, Obj->getContentSize().height / 2);

	RightPoint_ = Node::create();
	Obj->addChild(RightPoint_);
	RightPoint_->setPosition(Obj->getContentSize().width, Obj->getContentSize().height / 2);
	UpPoint_ = Node::create();
	Obj->addChild(UpPoint_);
	UpPoint_->setPosition(0, Obj->getContentSize().height);
	BulletPoint_ = Node::create();
	Obj->addChild(BulletPoint_);
	BulletPoint_->setPosition(Obj->getContentSize().width / 2, Obj->getContentSize().height / 2);
}
void CBaseBoss::OnHurtActionComplete()
{

}
void CBaseBoss::OnAttackActionComplete()
{

}
void CBaseBoss::OnSkillActionComplete()
{

}
void CBaseBoss::Update()
{
	CBattleObject::Update();
}
void CBaseBoss::OnIdle()
{
	CBattleObject::OnIdle();
}
void CBaseBoss::OnRun()
{
	CBattleObject::OnRun();
}
void CBaseBoss::OnAttack()
{
	CBattleObject::OnAttack();
}
void CBaseBoss::OnSkill()
{
	CBattleObject::OnSkill();
}
void CBaseBoss::OnHurt()
{
	CBattleObject::OnHurt();
}
CBaseBoss::~CBaseBoss()
{
}
