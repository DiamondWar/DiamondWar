#include "AudioManager.h"


CAudioManager::CAudioManager()
{
}


CAudioManager::~CAudioManager()
{
}
CAudioManager* CAudioManager::Instance_ = nullptr;
CAudioManager* CAudioManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CAudioManager();
	return Instance_;

}
