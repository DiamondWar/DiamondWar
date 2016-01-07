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
void CBattleObjectManager::AddSpellObject(CBattleObject* obj)
{
	SpellList_.pushBack(obj);
}
void CBattleObjectManager::AddObject(CBattleObject* obj)
{
	BattleList_.pushBack(obj);
}
void CBattleObjectManager::AddBulletObject(CBattleObject* obj)
{
	BulletList_.pushBack(obj);
}
void CBattleObjectManager::AddHurtShowObject(CHurtShow* obj)
{
	HurtShowList_.pushBack(obj);
}
void CBattleObjectManager::AddSoliderDie(CSoliderDie *obj)
{
	SoliderDieList_.pushBack(obj);
}
void CBattleObjectManager::AddBuffObject(CBuff* obj)
{
	BuffList_.pushBack(obj);
}
void CBattleObjectManager::DeleteObject(CBattleObject*obj)
{

}
void  CBattleObjectManager::DeleteObject(int id)
{

}
void CBattleObjectManager::SetFirstRanksBoss(CBaseBoss* boss)
{
	FirstRanksBoss_ = boss;
}
void CBattleObjectManager::SetSecondRanksBoss(CBaseBoss* boss)
{
	SecondRanksBoss_ = boss;
}
CBaseBoss* CBattleObjectManager::GetFirstRanksBoss()
{
	return FirstRanksBoss_;
}
CBaseBoss* CBattleObjectManager::GetSecondRanksBoss()
{
	return SecondRanksBoss_;
}
CBaseBoss* CBattleObjectManager::GetEnemyByRange(float rank, int type, float range, float r, float x, float y)
{
	CBaseBoss* sol = nullptr;
	int lastlength = 0;
	int attacktype = 0;

	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks != rank)
		{
			if ((type == 1 && keysol->Data_->SoliderType <= 2)||(type==2&&keysol->Data_->SoliderType>=2)||type==3)
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
	}
	if (sol == nullptr)
	{
		if (rank == 1)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, SecondRanksBoss_->Obj->getPosition().x, SecondRanksBoss_->Obj->getPosition().y);
			length = length  - r;
			if (length < range)
			{
				sol = SecondRanksBoss_;
			}
		}
		else
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, FirstRanksBoss_->Obj->getPosition().x, FirstRanksBoss_->Obj->getPosition().y);
			length = length - r;
			if (length < range)
			{
				sol = FirstRanksBoss_;
			}
		}
	}
	return sol;
}
Vector<CSolider*> CBattleObjectManager::GetLuDiEnemyListByRange(float rank, float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks != rank&&keysol->Data_->SoliderType <= 2)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length < range)
			{
				list.pushBack(keysol);
			}
		}
	}
	return list;
}
Vector<CSolider*> CBattleObjectManager::GetFeiXingEnemyListByRange(float rank, float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks != rank && (keysol->Data_->SoliderType == 3 || keysol->Data_->SoliderType == 2))
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length < range)
			{
				list.pushBack(keysol);
			}
		}
	}
	return list;
}
Vector<CSolider*> CBattleObjectManager::GetEnemyListByRange(float rank, float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks != rank)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length < range)
			{
				list.pushBack(keysol);
			}
		}
	}
	return list;
}
Vector<CSolider*> CBattleObjectManager::GetFriendListByRange(float rank, float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks == rank)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length < range)
			{
				list.pushBack(keysol);
			}
		}
	}
	return list;
}
Vector<CSolider*> CBattleObjectManager::GetLuDiFriendListByRange(float rank, float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks == rank)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length < range)
			{
				list.pushBack(keysol);
			}
		}
	}
	return list;
}
Vector<CSolider*> CBattleObjectManager::GetFeiXingFriendListByRange(float rank, float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if (keysol->IsDelete_ == true)
			continue;
		if (keysol->Ranks == rank)
		{
			float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
			length = length - keysol->RangeR_ - r;
			if (length < range)
			{
				list.pushBack(keysol);
			}
		}
	}
	return list;
}
Vector<CSolider*> CBattleObjectManager::GetSoliderListByRange(int type ,float range, float r, float x, float y)
{
	Vector<CSolider*> list;
	for (CBattleObject* key : BattleList_)
	{
		CSolider * keysol = static_cast<CSolider*>(key);
		if(keysol->IsDelete_ == true)
			continue;
		float length = CCGlobleConfig::GetLengthByPoint(x, y, keysol->Obj->getPosition().x, keysol->Obj->getPosition().y);
		length = length - keysol->RangeR_ - r;
		if (length < range)
		{
			if (type == 1)
			{
				if (keysol->Data_->SoliderType <= 2)
				{
					list.pushBack(keysol);
				}
			}
			else if (type == 2)
			{
				if (keysol->Data_->SoliderType >= 2)
				{
					list.pushBack(keysol);
				}
			}
			else
			{
				list.pushBack(keysol);
			}
			
		}
	}
	return list;
}
void CBattleObjectManager::Update()
{
	for (auto key : BattleList_)
	{
		if (key->IsDelete_ == false)
			key->Update();
	}
	for (auto key : BulletList_)
	{
		if (key->IsDelete_ == false)
			key->Update();
	}
	for (auto key : HurtShowList_)
	{
		if (key->IsDelete_ == false)
			key->Update();
	}
	for (auto key : BuffList_)
	{
		if (key->IsDelete_ == false)
			key->Update();
	}
	for (auto key : SoliderDieList_)
	{
		if (key->IsDelete_ == false)
			key->Update();
	}
	for (auto key : SpellList_)
	{
		if (key->IsDelete_ == false)
			key->Update();
	}
}
void CBattleObjectManager::ClearAllObject()
{
	BattleList_.clear();
	BulletList_.clear();
	HurtShowList_.clear();
	BuffList_.clear();
	SoliderDieList_.clear();
	SpellList_.clear();
}
