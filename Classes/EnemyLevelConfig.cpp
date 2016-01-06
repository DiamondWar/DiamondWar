#include "EnemyLevelConfig.h"
#include "CGlobleConfig.h"
USING_NS_CC;
CEnemyLevelConfig* CEnemyLevelConfig::Instance_ = nullptr;
CEnemyLevelConfig::CEnemyLevelConfig()
{
}


CEnemyLevelConfig::~CEnemyLevelConfig()
{
}
CEnemyLevelConfig* CEnemyLevelConfig::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CEnemyLevelConfig();
	return Instance_;
}
void CEnemyLevelConfig::LoadText()
{
	std::string  data = cocos2d::FileUtils::getInstance()->getStringFromFile(StressText);
	String* ns = CCString::createWithFormat("%s", data.c_str());
	CCArray* array = CCGlobleConfig::split(ns->getCString(), "\n");
	for (int i = 1; i < array->count(); i++)
	{
		String * str = static_cast<String*>(array->getObjectAtIndex(i));
		CCArray * strarray = CCGlobleConfig::split(str->getCString(), "\t");
		CEnemyLevelData *data = new CEnemyLevelData();
		int index = 0;
		String * str0 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ID = str0->intValue();
		str0->release();
		str0 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->ReadyTime = str0->floatValue()*60;
		str0->release();
		str0 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->RoleId = str0->intValue();
		str0->release();
		str0 = static_cast<String*>(strarray->getObjectAtIndex(index++));
		data->RoleName = str0->getCString();
		str0->release();
		DataList_.pushBack(data);

	}
	CCLOG(" data  == %s", ns->getCString());
}

CEnemyLevelData* CEnemyLevelConfig::GetItemById(int id)
{
	for (auto key : DataList_)
	{
		if (key->ID == id)
			return key;
	}
	return nullptr;
}
CEnemyLevelData* CEnemyLevelConfig::GetItemByIndex(int index)
{
	if (index<DataList_.size())
		return DataList_.at(index);
	return nullptr;
}
