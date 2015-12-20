#include "StrengthConfig.h"
#include "CGlobleConfig.h"
USING_NS_CC;
CStrengthConfig* CStrengthConfig::Instance_ = nullptr;
CStrengthConfig::CStrengthConfig()
{
}


CStrengthConfig::~CStrengthConfig()
{
}
CStrengthConfig* CStrengthConfig::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CStrengthConfig();
	return Instance_;
}
void CStrengthConfig::LoadText()
{
	std::string  data = cocos2d::FileUtils::getInstance()->getStringFromFile(StressText);
	String* ns = CCString::createWithFormat("%s", data.c_str());
	CCArray* array = CCGlobleConfig::split(ns->getCString(), "\n");
	for (int i = 1; i < array->count(); i++)
	{
		String * str = static_cast<String*>(array->getObjectAtIndex(i));
		CCArray * strarray = CCGlobleConfig::split(str->getCString(), "\t");
		CStrengthData *data = new CStrengthData();
		int index = 0;
		
		data->ID = i;
		String* str0 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->OneValue = str0->floatValue();
		str0->release();
		String * str1 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->TwoValue = str1->floatValue();
		str1->release();
		String * str2 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ThreeValue = str2->floatValue();
		str2->release();
		String * str3 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->FouthValue = str3->floatValue();
		str3->release();
		String * str7 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->fiveValue = str7->floatValue();
		str7->release();

		
		DataList_.pushBack(data);

	}
	CCLOG(" data  == %s", ns->getCString());
}

float CStrengthConfig::GetItemById(int id,int type)//第一个参数为多余的数量 第二个参数为本来所需费用
{
	for (auto key : DataList_)
	{
		if (key->ID == id)
		{
			if (type == 1)
			{
				return key->OneValue;
			}
			if (type == 2)
			{
				return key->TwoValue;
			}
			if (type == 3)
			{
				return key->ThreeValue;
			}
			if (type == 4)
			{
				return key->FouthValue;
			}
			if (type == 5)
			{
				return key->fiveValue;
			}
		}
	}
	return 1;
}
