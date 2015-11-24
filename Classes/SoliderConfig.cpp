#include "SoliderConfig.h"
#include "CGlobleConfig.h"
USING_NS_CC;
CSoliderConfig::CSoliderConfig()
{
}


CSoliderConfig::~CSoliderConfig()
{
}

void CSoliderConfig::LoadText()
{
	std::string  data = cocos2d::FileUtils::getInstance()->getStringFromFile(StressText);
	CCString* ns = CCString::createWithFormat("%s", data.c_str());
	CCArray* array = CCGlobleConfig::split(ns->getCString(), "\n");
	for (int i = 0; i < array->count(); i++)
	{
		CCString * str = static_cast<CCString*>(array->getObjectAtIndex(i));
		CCArray * strarray = CCGlobleConfig::split(str->getCString(), "\t");
	}
	CCLOG(" data  == %s", ns->getCString());
}