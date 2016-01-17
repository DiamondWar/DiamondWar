#include "GameDataManager.h"
#include "SoliderConfig.h"
#include "SpellConfig.h"
USING_NS_CC;
CGameDataManager::CGameDataManager()
{
	CSoliderData* data1 = CSoliderConfig::GetInstance()->GetItemById(1001);
	AllSoliderList_.pushBack(data1);
	CSoliderData* data2 = CSoliderConfig::GetInstance()->GetItemById(1002);
	AllSoliderList_.pushBack(data2);
	CSoliderData* data3= CSoliderConfig::GetInstance()->GetItemById(2001);
	AllSoliderList_.pushBack(data3);
	CSoliderData* data4 = CSoliderConfig::GetInstance()->GetItemById(2002);
	AllSoliderList_.pushBack(data4);
	CSoliderData* data5 = CSoliderConfig::GetInstance()->GetItemById(3001);
	AllSoliderList_.pushBack(data5);
	CSoliderData* data6 = CSoliderConfig::GetInstance()->GetItemById(3002);
	AllSoliderList_.pushBack(data6);
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