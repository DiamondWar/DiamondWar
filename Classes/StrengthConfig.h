#pragma once
#include "cocos2d.h"
#include "StrengthData.h"
class CStrengthConfig
{
public :
	CStrengthConfig();
	~CStrengthConfig();

	void LoadText();
	static CStrengthConfig* GetInstance();
	float GetItemById(int id, int type);
	cocos2d::Vector<CStrengthData*> DataList_;
private:
	std::string  StressText = "Strength_Config.txt";
	static CStrengthConfig* Instance_;
};

