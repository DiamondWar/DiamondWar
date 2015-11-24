#include "BattleObjectManager.h"
USING_NS_CC;


CBattleObjectManager::CBattleObjectManager()
{
}


CBattleObjectManager::~CBattleObjectManager()
{
	BattleList_.clear();
	Instance_ = nullptr;
}

CBattleObjectManager* CBattleObjectManager::Instance_ = nullptr;
CBattleObjectManager* CBattleObjectManager::GetInstance()
{
	if (Instance_ == nullptr)
	{
		Instance_ = new CBattleObjectManager();
	}
	return Instance_;
}
void CBattleObjectManager::AddObject(CBattleObject* obj)
{
	BattleList_.insert(BattleList_.size(), obj);
}
void CBattleObjectManager::AddBulletObject(CBullet* obj)
{
	BulletList_.insert(BulletList_.size(), obj);
}
void CBattleObjectManager::DeleteObject(CBattleObject*obj)
{

}
void  CBattleObjectManager::DeleteObject(int id)
{

}
CSolider* CBattleObjectManager::GetEnemyByRange(float rank, float range,float r , float x, float y)
{
	CSolider* sol = nullptr;
	int lastlength = 0;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->Ranks != rank)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length< range)
			{
				if (sol == nullptr)
				{
					lastlength = length;
					sol = keysol;
				}
				else
				{
					if (lastlength>length)
					{
						lastlength = length;
						sol = keysol;
					}
				}
			}
		}
	}
	return sol;
}

void CBattleObjectManager::Update()
{
	for (auto key : BattleList_)
	{
		if (key->IsDelete_==false)
			key->Update();
	}
	for (auto key: BulletList_)
	{
		if (key->IsDelete_ == false)
			key ->Update();
	}
}
void CBattleObjectManager::ClearAllObject()
{
	BattleList_.clear();
}
