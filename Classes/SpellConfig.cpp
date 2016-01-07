#include "SpellConfig.h"
#include "CGlobleConfig.h"
USING_NS_CC;
CSpellConfig* CSpellConfig::Instance_ = nullptr;
CSpellConfig::CSpellConfig()
{
}


CSpellConfig::~CSpellConfig()
{
}
CSpellConfig* CSpellConfig::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CSpellConfig();
	return Instance_;
}
void CSpellConfig::LoadText()
{
	std::string  data = cocos2d::FileUtils::getInstance()->getStringFromFile(StressText);
	String* ns = CCString::createWithFormat("%s", data.c_str());
	CCArray* array = CCGlobleConfig::split(ns->getCString(), "\n");
	for (int i = 1; i < array->count(); i++)
	{
		String * str = static_cast<String*>(array->getObjectAtIndex(i));
		CCArray * strarray = CCGlobleConfig::split(str->getCString(), "\t");
		CSpellData *data = new CSpellData();
		int index = 0;
		String * str0 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ID = str0->intValue();
		str0->release();
		String * str1 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->Name = str1->getCString();
		str1->release();
		str1 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->NeedStar_ = str1->intValue();
		str1->release();
		String * str2 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->TargetRank = str2->intValue();
		str2->release();
		String * str3 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->TargetType = str3->intValue();
		str3->release();
		String *str7 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->AttackPoint = str7->intValue();
		str7->release();
		String * str6 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->Hurt = str6->intValue();
		str6->release();
		String * str4 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->BulletType = str4->intValue();
		str4->release();
		String * str5 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		CCArray* carr = CCGlobleConfig::split(str5->getCString(), ",");
		for (int n = 0; n < carr->count(); n++)
		{
			data->BulletValue[n] = static_cast<String*>(carr->getObjectAtIndex(n))->floatValue();
		}
		str5->release();

		String * str9 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->EffectId = str9->intValue();
		str9->release();
		String* str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		CCArray* carr1 = CCGlobleConfig::split(str10->getCString(), ",");
		for (int n = 0; n < carr1->count(); n++)
		{
			data->EffectValue[n] = static_cast<String*>(carr1->getObjectAtIndex(n))->floatValue();
		}

		str10->release();

		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ResourceName1 = str10->getCString();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ResourceFrameCount1 = str10->intValue();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ResourceName2 = str10->getCString();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ResourceFrameCount2 = str10->intValue();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ResourceName3 = str10->getCString();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ResourceFrameCount3 = str10->intValue();
		str10->release();

		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->AttackVoice = str10->getCString();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->HitVoice = str10->getCString();
		str10->release();
		str10 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->Desc = str10->getCString();
		str10->release();
		data->updateResouce();
		DataList_.pushBack(data);
	}
}

CSpellData* CSpellConfig::GetItemById(int id)
{
	for (auto key : DataList_)
	{
		if (key->ID == id)
			return key;
	}
	return nullptr;
}
