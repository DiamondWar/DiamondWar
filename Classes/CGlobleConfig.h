#pragma once
#include "cocos2d.h"
#include <math.h> 
#define PI 3.1415926
class CCGlobleConfig
{
public:
	static const int  COMMON_VALUE = 2;
	static const int  COMMON_RANGE_VALUE =50;
	static const int  COMMON_BULLETRANGE_VALUE = 10;
	static const int  COMMON_BULLESPEED_VALUE = 1;
	static const int COMMON_ATTACK_VALUE = 1;
	static  long Game_time ;
	static const int COMMON_LOAD_POINT = 400;
	static const int COMMON_SKY_POINT = 720;
	static float GetLengthByPoint(float point1_x, float point1_y, float point2_x, float point2_y);
	static float getLengthByCircle(float point1_x, float point1_y, float point2_x, float point2_y);
	static float GetAngleByPoint(float point1_x, float point1_y, float point2_x, float point2_y);
	static long GetCurrntTime();
	static cocos2d::CCArray* split(const char* srcStr, const char* sSep);
	static cocos2d::Sprite* maskedSpriteWithSprite(cocos2d::Sprite* textureSprite, float size, cocos2d::Sprite* maskSprite);
};

