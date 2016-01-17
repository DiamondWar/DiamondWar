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
	if (index < 6)
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
	CSoliderData * Data_ = CSoliderConfig::GetInstance()->GetItemById(id);
	if (Data_->NeedStar == 5 && Data_->SoliderType == 1 && ranks == 1)
	{
		if (CCGlobleConfig::IsMyGolden == true)
			return;
		CCGlobleConfig::IsMyGolden = true;
		CGameSceneControl::GetInstance()->OnScreenScale();
		CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(1, 3);
	}
	else if (ranks == 2 && Data_->NeedStar == 4 && Data_->SoliderType == 3)
	{
		if (CCGlobleConfig::IsEnemyHaHa == true)
			return;
		CCGlobleConfig::IsEnemyHaHa = true;
		CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(2, 2.5);
	}
	else if (ranks == 1 && Data_->NeedStar == 4 && Data_->SoliderType == 3)
	{
		CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(6, 2.5);
	}
	else if (ranks == 2 && Data_->SoliderType == 2 && Data_->NeedStar == 3)
	{
		if (CCGlobleConfig::isEnemyHeroPower == true)
			return;
		CCGlobleConfig::isEnemyHeroPower = true;
		CGameSceneControl::GetInstance()->GetBattleUIManager()->OnPlayVoice(7, 2.5);
	}
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
void CGameSceneControl::OnScreenScale(float x)
{
	GameRoot_->stopAllActions();
	//GameRoot_->setPosition(-1900, 0);
	MoveTo* moveto = MoveTo::create(0.5, Vec2(x, -150));
	MoveTo* moveto1 = MoveTo::create(0.5, Vec2(0, 0));
	ScaleTo* scalto = ScaleTo::create(0.5, 1.8);
	ScaleTo* scalto1 = ScaleTo::create(1.5, 1.8);
	ScaleTo* scalto2 = ScaleTo::create(0.5, 1);
	CCSpawn* spawn = CCSpawn::create(moveto, scalto, NULL);
	CCSpawn*spawn1 = CCSpawn::create(moveto1, scalto2, NULL);
	CCSequence* sequence = CCSequence::create(spawn, scalto1, spawn1, NULL);
	GameRoot_->runAction(sequence);
}
void CGameSceneControl::SetBattleUIManager(CBattleUIManager* manager)
{
	BattleManager_ = manager;
}
CBattleUIManager* CGameSceneControl::GetBattleUIManager()
{
	return BattleManager_;
}
CGameSceneControl::~CGameSceneControl()
{
}
