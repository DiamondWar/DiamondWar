#include "GameSceneControl.h"
#include "Solider.h"
#include "BattleObjectManager.h"
#include "SoliderConfig.h"
#include "Shake.h"
USING_NS_CC;
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
	HeroList[0] = 1001;
	HeroList[1] = 1002;
	HeroList[2] = 1003;
	HeroList[3] = 2001;
	HeroList[4] = 2002;
	HeroList[5] = 2003;
	HeroList[6] = 3001;
	HeroList[7] = 3002;
	HeroList[8] = 3003;
}
bool CGameSceneControl::IsHaveConsumeHero(int color, int num)
{
	int chosenum = -1;
	int index = -1;
	for (int i = 0; i < 9;i++)
	{
		CSoliderData * data = CSoliderConfig::GetInstance()->GetItemById(HeroList[i]);
		if (data->SoliderType == color)
		{
			if (data->NeedStar < num)
			{
				if (chosenum < data->NeedStar)
				{
					chosenum = data->NeedStar;
					index = i;
				}
			}
			else if (data->NeedStar == num)
			{
				chosenum = num;
				index = i;
				break;
			}
		}
	}
	if (chosenum == -1)
	{
		return false;
	}
	float x = chosenum + 0.0;
	float y = num + 0.0;
	CreateSolider(HeroList[index], 1, 1);
	int r = random(0, 8);
	CreateSolider(HeroList[r], 2, 1);
	return true;
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
void CGameSceneControl::AddScreenShake()
{
	Shake*sk = Shake::create(3, 3);
	GameRoot_->runAction(sk);
}
CGameSceneControl::~CGameSceneControl()
{
}
