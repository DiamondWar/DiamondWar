#include "VideoManager.h"


CVideoManager::CVideoManager()
{
}


CVideoManager::~CVideoManager()
{
}
CVideoManager* CVideoManager::Instance_ = nullptr;
CVideoManager* CVideoManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CVideoManager();
	return Instance_;
}

