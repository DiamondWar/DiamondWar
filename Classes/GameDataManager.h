#pragma once
#include "cocos2d.h"
#include "SoliderData.h"
#include "SpellData.h"
class CGameDataManager
{
public:
	CGameDataManager();
	~CGameDataManager();
	static CGameDataManager* GetInstance();
	bool IsHaveHeroByNeedStar(int start, int type);
	cocos2d::Vector<CSoliderData*> GetHeroListByNeedStar(int star,int type);
	cocos2d::Vector<CSpellData*> GetSpellListByNeedStar(int star); 
private: 
	static CGameDataManager* Instance_;
	cocos2d::Vector<CSoliderData*>AllSoliderList_;
	cocos2d::Vector<CSpellData*>AllSpellList_;
};

