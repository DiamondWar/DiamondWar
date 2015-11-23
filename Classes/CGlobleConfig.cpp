#include "CGlobleConfig.h"
#include "cocos2d.h"

float CCGlobleConfig::GetLengthByPoint(float point1_x, float point1_y, float point2_x, float point2_y)
{
	float x = abs(point1_x - point2_x);
	float y = abs(point1_y - point2_y);
	float length = sqrt(x*x + y*y);
	return length;
}
long CCGlobleConfig::GetCurrntTime()
{
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);

	int day = tm->tm_mday;
	int hour = tm->tm_hour;
	int minute = tm->tm_min;
	int second = tm->tm_sec;
	long ltime = second + minute * 60 + hour * 3600;
	return ltime;
}