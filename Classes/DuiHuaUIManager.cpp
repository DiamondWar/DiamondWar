#include "DuiHuaUIManager.h"
#include "CGlobleConfig.h"
#include "AudioManager.h"
CDuiHuaUIManager::CDuiHuaUIManager()
{
}


CDuiHuaUIManager::~CDuiHuaUIManager()
{
}
bool CDuiHuaUIManager::init()
{
	if (!Node::init())
		return false;
	scheduleUpdate();
	return true;
}
void CDuiHuaUIManager::update(float detal)
{
	if (CCGlobleConfig::GetCurrntTime() > startTime + ContinueTime)
	{
		Delegate_->OnAudioComplete(Audio_Index);
		removeFromParent();
		CAudioManager::GetInstance()->ResumeBackground();
	}
}
void CDuiHuaUIManager::PlayPersonAudio(int index, float time, CAudioDelegate*delega)
{
	startTime = CCGlobleConfig::GetCurrntTime();
	ContinueTime = time * 1000;
	Audio_Index = index;
	Delegate_ = delega;
	switch (index)
	{
	case 1:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nan_golden");
		break;
	case 2:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nan_haha");
		break;
	case 3:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nan_welcome");
		break;
	case 4:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nan_welldone");
		break;
	case 5:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nv_caiseshuijing");
		break;
	case 6:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nv_choice");
		break;
	case  7:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nv_heropower");
		break;
	case 8:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nv_hewin");
		break;
	case 9:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nv_monkey");
		break;
	case 10:
		CAudioManager::GetInstance()->PlayerPersonVoice("audio_nv_start");
		break;
	default:
		break;
	}
}