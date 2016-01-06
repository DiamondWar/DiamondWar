#pragma once
#include "EnemyLevelData.h"
class CEnemyLevelConfig
{
public:
	CEnemyLevelConfig();
	~CEnemyLevelConfig();

	void LoadText();
	static CEnemyLevelConfig* GetInstance();
	CEnemyLevelData* GetItemById(int id);
	CEnemyLevelData* GetItemByIndex(int index);
	cocos2d::Vector<CEnemyLevelData*> DataList_;
private:
	std::string  StressText = "EnemyLevelConfig.txt";
	static CEnemyLevelConfig* Instance_;
};