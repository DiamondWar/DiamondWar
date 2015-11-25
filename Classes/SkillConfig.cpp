#include "SkillConfig.h"
#include "CGlobleConfig.h"
USING_NS_CC;
CSkillConfig* CSkillConfig::Instance_ = nullptr;
CSkillConfig::CSkillConfig()
{
}


CSkillConfig::~CSkillConfig()
{
}
CSkillConfig* CSkillConfig::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CSkillConfig();
	return Instance_;
}
void CSkillConfig::LoadText()
{
	std::string  data = cocos2d::FileUtils::getInstance()->getStringFromFile(StressText);
	CCString* ns = CCString::createWithFormat("%s", data.c_str());
	CCArray* array = CCGlobleConfig::split(ns->getCString(), "\n");
	for (int i = 1; i < array->count(); i++)
	{
		CCString * str = static_cast<CCString*>(array->getObjectAtIndex(i));
		CCArray * strarray = CCGlobleConfig::split(str->getCString(), "\t");
		CSkillData *data = new CSkillData();
		int index = 0;
		CCString * str0 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->ID = str0->intValue();
		str0->release();
		CCString * str1 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Name = str1->getCString();
		str1->release();
		CCString * str2 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->TargetRank = str2->intValue();
		str2->release();
		CCString * str3 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->TargetType = str3->intValue();
		str3->release();
		CCString * str4 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->BulletType = str4->intValue();
		str4->release();
		CCString * str5 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->BulletValue = str5->getCString();
		str5->release();
		CCString * str6 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->HurtCf = str6->intValue();
		str6->release();
		CCString * str7 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->CoolTime = str7->intValue();
		str7->release();
		CCString * str8 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->AttributeInfo = str8->getCString();
		str8->release();
		CCString * str9 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->EffectId = str9->intValue();
		str9->release();
		CCString * str10 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->EffectCf = str10->intValue();
		str10->release();
		str10 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->EffectVale = str10->getCString();
		str10->release();
		str10 = static_cast<CCString*>(strarray->getObjectAtIndex(index++));
		data->Desc = str10->getCString();
		str10->release();
		DataList_.insert(DataList_.size(), data);

	}
	CCLOG(" data  == %s", ns->getCString());
}

CSkillData* CSkillConfig::GetItemById(int id)
{
	for (auto key : DataList_)
	{
		if (key->ID == id)
			return key;
	}
	return nullptr;
}
