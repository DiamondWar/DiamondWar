#pragma once
#include "cocos2d.h"
#include <math.h> 
class CCGlobleConfig
{
public:
	static const int  COMMON_VALUE = 4;
	static const int COMMON_ATTACK_VALUE = 1000;
	static  long Game_time ;
	static float GetLengthByPoint(float point1_x, float point1_y, float point2_x, float point2_y);
	static long GetCurrntTime();
	static cocos2d::CCArray* split(const char* srcStr, const char* sSep);
};

