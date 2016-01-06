
#include "SustainBullet.h"
#include "BattleObjectManager.h"
#include "GameSceneControl.h"
USING_NS_CC;
CSustainBullet::CSustainBullet(CAttackData* data, int x, int y, CBuffData*  damage, CBaseBoss* target, int rank, int type)
{
	Data_ = data;
	Init_x = x;
	Init_y = y;
	Ranks_ = rank;
	RangeR_ = 10;
	BuffData = damage;
	AtTarget_ = target;
	Data_->BulletType = 2;
	FrameCount = 6;
	MaxBulletNum = Data_->BulletValue[2];
	IsCanCreateBullet = true;

	for (int i = 0; i < MaxBulletNum;i++)
	{
		CBullet* bullet = new CBullet(Data_, Init_x, Init_y, BuffData, AtTarget_, Ranks_, 2);
		bullet->IsDelete_ = true;
		bullet->Obj->setVisible(false);
		CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
		CBattleObjectManager::GetInstance()->GetInstance()->AddBulletObject(bullet);
		bulletlist.pushBack(bullet);
	}
}


CSustainBullet::~CSustainBullet()
{
	bulletlist.clear();
}
void CSustainBullet::OnResourceLoadComplete()
{
}
//动作播放完成
void CSustainBullet::OnHurtActionComplete()
{

}
void CSustainBullet::OnAttackActionComplete()
{

}
void CSustainBullet::OnSkillActionComplete()
{

}
void CSustainBullet::Update()
{

	if (IsDelete_ == true)
		return;
	CBattleObject::Update();
	if (curFrameCount%FrameCount == 0 && IsCanCreateBullet == true)
	{
		BulletNum++;
		bulletlist.at(BulletNum-1)->IsDelete_ = false;
		bulletlist.at(BulletNum - 1)->Obj->setVisible(true);
		if (BulletNum == MaxBulletNum)
		{
			IsDelete_ = true;
			return;
		}
	}
	curFrameCount++;
}