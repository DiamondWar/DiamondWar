#pragma once
#include "cocos2d.h"
class CEnemyLevelData:public cocos2d::Node
{
public:
	CEnemyLevelData();
	~CEnemyLevelData();

	 int ID;
	 int ReadyTime;
	 int RoleId;
	 std::string RoleName;
};

