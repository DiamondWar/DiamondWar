#include "BaseBoss.h"


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
	CurHp = 10000;
	MaxHp = 10000;
	InitObj();
	
}
void CBaseBoss::OnResourceLoadComplete()
{
	Obj->setPosition(Init_x, Init_y);
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

CBaseBoss::~CBaseBoss()
{
}
