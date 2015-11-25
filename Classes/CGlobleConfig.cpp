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
long CCGlobleConfig::Game_time = 0;

cocos2d::CCArray* CCGlobleConfig::split(const char* srcStr, const char* sSep)
{
	cocos2d::CCArray* stringList = cocos2d::CCArray::create();
	stringList->retain();
	int size = strlen(srcStr);
	/* 将数据转换为Cocos2d-x字符串对象 */
	cocos2d::CCString* str = cocos2d::CCString::create(srcStr);
	int startIndex = 0;
	int endIndex = 0;
	endIndex = str->_string.find(sSep);
	cocos2d::CCString* spliStr = NULL;
	while (endIndex > 0)
	{
		spliStr = cocos2d::CCString::create("");
		spliStr->retain();
		spliStr->_string = str->_string.substr(startIndex, endIndex);
		stringList->addObject(spliStr);
		str->_string = str->_string.substr(endIndex + 1, size);
		endIndex = str->_string.find(sSep);
	}
	if (str->_string.compare("") != 0) {
		stringList->addObject(cocos2d::CCString::create(str->_string));
	}
	return stringList;
}