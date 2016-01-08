#include "SpellLiuXingManager.h"
#include "CGlobleConfig.h"
#include "SpellLiuXingBullet.h"
#include "BattleObjectManager.h"
#include "GameSceneControl.h"
USING_NS_CC;
CSpellLiuXingManager::CSpellLiuXingManager(CSpellData* data)
{
	InvertalTime =  data->BulletValue[1] * 1000;
	int helo =700;
	 Hurt = data->Hurt;
	Init_Point[5] = 1700 - helo;
	Init_Point[4] = 100 - helo;
	Init_Point[2] = 400 - helo;
	Init_Point[0] = 700 - helo;
	Init_Point[3] = 1100 - helo;
	Init_Point[1] = 1500 - helo;
	BulletNum = 0;
	MaxBulletNum = data->BulletValue[2];
	BuffData_ = new CBuffData();
	BuffData_->attackPoint = data->AttackPoint;
	BuffData_->ContinueTime = 0;
	BuffData_->AttackType = 3;
	BuffData_->From = nullptr;
	BuffData_->Target = nullptr;
	BuffData_->ResourceFrameCount = data->ResourceFrameCount2;
	BuffData_->ResourceName = data->ResourceName2;
	AttackData_ = new CAttackData();
	AttackData_->AttackPoint = data->AttackPoint;
	AttackData_->BulletType = data->BulletType;
	AttackData_->BulletValue[1] = data->BulletValue[0]*2;
	AttackData_->ResourceName1 = data->ResourceName1;
	AttackData_->ResourceFrameCount1 = data->ResourceFrameCount1;

	EffctBuffData_ = new CBuffData();
	EffctBuffData_->attackPoint = data->AttackPoint;
	EffctBuffData_->ContinueTime = 0;
	EffctBuffData_->AttackType = 3;
	EffctBuffData_->From = nullptr;
	EffctBuffData_->Target = nullptr;
	EffctBuffData_->ResourceFrameCount =0;
	EffctBuffData_->ResourceName = "";
	EffectData_ = new CAttackData();
	EffectData_->AttackPoint = data->AttackPoint;
	EffectData_->BulletType = data->BulletType;
	EffectData_->BulletValue[1] = 10;
	EffectData_->ResourceName1 = data->ResourceName3;
	EffectData_->ResourceFrameCount1 = data->ResourceFrameCount3;
	LastAttackTime = CCGlobleConfig::GetCurrntTime();
	lastEffectTime = CCGlobleConfig::GetCurrntTime();

}


CSpellLiuXingManager::~CSpellLiuXingManager()
{

}
void CSpellLiuXingManager::OnResourceLoadComplete()
{}
void CSpellLiuXingManager::OnHurtActionComplete()
{}
void CSpellLiuXingManager::OnSkillActionComplete()
{}
void CSpellLiuXingManager::OnAttackActionComplete()
{}
void CSpellLiuXingManager::Update()
{
	if (EffectNum >= MaxEffectNum&&BulletNum >= MaxBulletNum)
	{
		IsDelete_ = true;
	}
	NowTime = CCGlobleConfig::GetCurrntTime();
	if (EffectNum >= MaxEffectNum*0.5)
	{
		if (NowTime > LastAttackTime + InvertalTime)
		{
			LastAttackTime = NowTime;
			if (BulletNum >= MaxBulletNum)
			{
				return;
			}
			//发射一个子弹
			CSpellLiuXingBullet* bullet = new CSpellLiuXingBullet(AttackData_, Init_Point[BulletNum % 6], 1400, BuffData_, 800, 1, 2);
			CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet->Obj);
			CBattleObjectManager::GetInstance()->AddBulletObject(bullet);
			BulletNum++;
			if (BulletNum == MaxBulletNum*3/4)
			{
				CGameSceneControl::GetInstance()->AddScreenShake();
				Vector<CSolider*> list = CBattleObjectManager::GetInstance()->GetEnemyListByRange(1, 2000, 0, 960, 540);
				for (int i = 0; i < list.size();i++)
				{
					list.at(i)->GetDamage(Hurt, 3);
				}
			}
		}
	}
	if (EffectNum<MaxEffectNum)
	{
		
		if (NowTime > lastEffectTime + 30)
		{
			lastEffectTime = NowTime;
			//发射一个子弹
			CSpellLiuXingBullet* bullet1 = new CSpellLiuXingBullet(EffectData_, EffectNum % 15 * 200 - 500, 1200+EffectNum%2*100, EffctBuffData_, 1300, 1, 2);
			CGameSceneControl::GetInstance()->GameRoot_->addChild(bullet1->Obj);
			bullet1->Obj->setScale(0.6, 4);
			CBattleObjectManager::GetInstance()->AddBulletObject(bullet1);
			EffectNum++;
		}
	}
	
	
	
}