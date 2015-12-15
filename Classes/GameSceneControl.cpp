#include "GameSceneControl.h"
#include "Solider.h"
#include "BattleObjectManager.h"
#include "SoliderConfig.h"
CGameSceneControl* CGameSceneControl::Instance_ = nullptr;

CGameSceneControl* CGameSceneControl::GetInstance()
{
	if (Instance_ == nullptr)
	{
		Instance_ = new CGameSceneControl();
	}
	return Instance_;
}
CGameSceneControl::CGameSceneControl()
{
}
void  CGameSceneControl::InitGameData()
{
	HeroList[0] = 101;
	HeroList[1] = 102;
	HeroList[2] = 201;
	HeroList[3] = 202;
	HeroList[4] = 301;
	HeroList[5] = 302;
	HeroList[6] = 401;
	HeroList[7] = 402;
}
bool CGameSceneControl::IsHaveConsumeHero(int color, int num)
{
	for (int i = 0; i < 6;i++)
	{
		CSoliderData * data = CSoliderConfig::GetInstance()->GetItemById(HeroList[i]);
		if (data->SoliderType == color&&data->NeedStar <= num)
		{
			float x = data->NeedStar+0.0;
			float y = num + 0.0;
			CreateSolider(HeroList[i], 1, y / x);
			CreateSolider(HeroList[i], 2, y / x);
			return true;
		}
	}
	return false;
}
void CGameSceneControl::CreateSolider(int id, int ranks,float level)
{
	CSolider* sol = new CSolider(id, 1, ranks,level);
	GameRoot_->addChild(sol->Obj);
	CBattleObjectManager::GetInstance()->AddObject(sol);
}
void CGameSceneControl::CreateBoss(int ranks)
{
	CBaseBoss* boss = new CBaseBoss(ranks);
	GameRoot_->addChild(boss->Obj);
	if (ranks==1)
	CBattleObjectManager::GetInstance()->SetFirstRanksBoss(boss);
	else 
		CBattleObjectManager::GetInstance()->SetSecondRanksBoss(boss);
}
void CGameSceneControl::SetRoot(cocos2d::Node* root)
{
	GameRoot_ = root;
}

CGameSceneControl::~CGameSceneControl()
{
}
