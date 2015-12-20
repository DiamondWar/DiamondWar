#pragma once
#include "cocos2d.h"
class CStrengthData:public cocos2d::Node
{
public:
	CStrengthData();
	~CStrengthData();
	int ID;
	float OneValue;// 1费兵消耗
	float TwoValue;// 2费兵消耗
	float ThreeValue;// 3费兵消耗
	float FouthValue;// 4费兵消耗
	float fiveValue;// 5费兵消耗
};

