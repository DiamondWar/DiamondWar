#pragma once
#include "SpellData.h"
class CSpellConfig
{
public:
	CSpellConfig();
	~CSpellConfig();
	void LoadText();
	static CSpellConfig* GetInstance();
	CSpellData* GetItemById(int id);
private:
	std::string  StressText = "SpellConfig.txt";
	static CSpellConfig* Instance_;
	cocos2d::Vector<CSpellData*> DataList_;
};
