#include "GameDataManager.h"


CGameDataManager::CGameDataManager()
{
}


CGameDataManager::~CGameDataManager()
{
}

CGameDataManager* CGameDataManager::Instance_ = nullptr;
CGameDataManager* CGameDataManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CGameDataManager();
	return Instance_;
}