#include "GameDataManager.h"
#include "SoliderConfig.h"
#include "SpellConfig.h"
USING_NS_CC;
CGameDataManager::CGameDataManager()
{
	AllSoliderList_ = CSoliderConfig::GetInstance()->DataList_;
	AllSpellList_ = CSpellConfig::GetInstance()->DataList_;
}


CGameDataManager::~CGameDataManager()
{
}

CGameDataManager* CGameDataManager::Instance_ = nullptr;
CGameDataManager* CGameDataManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CGameDataManager();
	return Instance_;
}
bool  CGameDataManager::IsHaveHeroByNeedStar(int start, int type)
{
	if (type <= 3)
	{
		for (auto key : AllSoliderList_)
		{
			if (key->SoliderType == type&& key->NeedStar == start)
			{
				return true;
			}
		}
	}
	else
	{
		for (auto key : AllSpellList_)
		{
			if (key->NeedStar_ == start)
				return true;
		}
	}
	
	return false;
}
Vector<CSoliderData*>CGameDataManager::GetHeroListByNeedStar(int star, int type)
{
	Vector<CSoliderData*> list;
	for (auto key : AllSoliderList_)
	{
		if (key->SoliderType == type&& key->NeedStar == star)
			list.pushBack(key);
	}
	return list;
}
Vector<CSpellData*>CGameDataManager::GetSpellListByNeedStar(int star)
{
	Vector<CSpellData*> list;
	for (auto key : AllSpellList_)
	{
		if ( key->NeedStar_ == star)
			list.pushBack(key);
	}
	return list;
}