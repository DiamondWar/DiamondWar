#include "SoliderConfig.h"
#include "CGlobleConfig.h"
USING_NS_CC;



CSoliderConfig* CSoliderConfig::Instance_ = nullptr;


CSoliderConfig::CSoliderConfig()
{
}


CSoliderConfig::~CSoliderConfig()
{
}

CSoliderConfig* CSoliderConfig::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CSoliderConfig();
	return Instance_;
}

void CSoliderConfig::LoadText()
{
	std::string  data = cocos2d::FileUtils::getInstance()->getStringFromFile(StressText);
	CCString* ns = CCString::createWithFormat("%s", data.c_str());
	CCArray* array = CCGlobleConfig::split(ns->getCString(), "\n");
	for (int i = 1; i < array->count(); i++)
	{
		CCString * str = static_cast<CCString*>(array->getObjectAtIndex(i));
		CCArray * strarray = CCGlobleConfig::split(str->getCString(), "\t");
		int index = 0;
		CSoliderData *data = new CSoliderData();
		CCString * str0 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->ID = str0->intValue();
		str0->release();
		CCString * str1 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Name = str1->getCString();
		str1->release();
		CCString * str2 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Type = str2->intValue();
		str2->release();
		CCString * str3 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->NeedStar = str3->intValue();
		str3->release();
		CCString * str4 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->AttackId = str4->intValue();
		str4->release();
		CCString * str5 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->SkillId = str5->intValue();
		str5->release();
		CCString * str6 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Attack = str6->intValue();
		str6->release();
		CCString * str7 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Blood = str7->intValue();
		str7->release();
		CCString * str8 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->MoveSpeed = str8->floatValue();
		str8->release();
		CCString * str9 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->AttackRange = str9->floatValue();
		str9->release();
		CCString * str10 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Desc = str10->getCString();
		str10->release();
		DataList_.insert(DataList_.size(), data);
		CCLOG(" data  == %s", ns->getCString());
	}
}
CSoliderData*  CSoliderConfig::GetItemById(int id)
{
	for (CSoliderData* key : DataList_)
	{
		if (key->ID == id)
			return key;
	}
	return nullptr;
}