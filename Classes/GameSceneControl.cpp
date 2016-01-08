#include "GameSceneControl.h"
#include "Solider.h"
#include "BattleObjectManager.h"
#include "SoliderConfig.h"
#include "Shake.h"
#include "SpellConfig.h"
#include "SpellData.h"
#include "SpellConfig.h"
#include "SpellManager.h"
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
	HeroList[2] = 2001;
	HeroList[3] = 2002;
	HeroList[4] = 3001;
	HeroList[5] = 3002;
	HeroList[6] = 1;
	HeroList[7] = 2;
}
int CGameSceneControl::IsHaveHero(int color, int num)
{
	int chosenum = -1;
	int index = -1;
	for (int i = 0; i < 8; i++)
	{
		if (i < 6)
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
		else
		{
			CSpellData* spell = CSpellConfig::GetInstance()->GetItemById(HeroList[i]);
			if (4 == color)
			{
				if (spell->NeedStar_ < num)
				{
					if (chosenum < spell->NeedStar_)
					{
						chosenum = spell->NeedStar_;
						index = i;
					}
				}
				else if (spell->NeedStar_ == num)
				{
					chosenum = num;
					index = i;
					break;
				}
			}
		}
		
	}
	return index;
}
bool CGameSceneControl::IsHaveConsumeHero(int color, int num)
{
	int chosenum = -1;
	int index = -1;
	for (int i = 0; i < 8; i++)
	{
		if (i < 6)
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
		else
		{
			CSpellData* spell = CSpellConfig::GetInstance()->GetItemById(HeroList[i]);
			if (4 == color)
			{
				if (spell->NeedStar_ < num)
				{
					if (chosenum < spell->NeedStar_)
					{
						chosenum = spell->NeedStar_;
						index = i;
					}
				}
				else if (spell->NeedStar_ == num)
				{
					chosenum = num;
					index = i;
					break;
				}
			}
		}
	}
	if (chosenum == -1)
	{
		return false;
	}
	float x = chosenum + 0.0;
	float y = num + 0.0;
	if (index<6)
		CreateSolider(HeroList[index], 1, 1);
	else
	{
		CreateSpell(HeroList[index]);
	}
	return true;
}
void CGameSceneControl::CreateSolider(int id, int ranks, float level)
{
	CCLOG("Id === %d", id);
	CSolider* sol = new CSolider(id, 1, ranks, level);
	GameRoot_->addChild(sol->Obj);
	CBattleObjectManager::GetInstance()->AddObject(sol);
}
void CGameSceneControl::CreateBoss(int ranks)
{
	CBaseBoss* boss = new CBaseBoss(ranks);
	GameRoot_->addChild(boss->Obj);
	if (ranks == 1)
		CBattleObjectManager::GetInstance()->SetFirstRanksBoss(boss);
	else
		CBattleObjectManager::GetInstance()->SetSecondRanksBoss(boss);
}
void CGameSceneControl::CreateSpell(int id)
{
	CSpellData* data = CSpellConfig::GetInstance()->GetItemById(id);
	CSpellManager::GetInstance()->ChoseSpell(data);
}
void CGameSceneControl::SetRoot(cocos2d::Node* root)
{
	GameRoot_ = root;
}
void CGameSceneControl::AddScreenShake()
{
	Shake*sk = Shake::create(3, 4);
	GameRoot_->runAction(sk);
}
CGameSceneControl::~CGameSceneControl()
{
}
