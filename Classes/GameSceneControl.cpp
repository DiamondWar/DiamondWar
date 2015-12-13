#include "GameSceneControl.h"
#include "Solider.h"
#include "BattleObjectManager.h"
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

void CGameSceneControl::CreateSolider(int id, int ranks)
{
	CSolider* sol = new CSolider(id, 1, ranks);
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
