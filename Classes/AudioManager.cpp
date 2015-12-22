#include "AudioManager.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC; 
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
void CAudioManager::PlayerBackGroundMusic(std::string music)
{
	if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		String*str = String::createWithFormat("Audio/%s", music.c_str());
		SimpleAudioEngine::getInstance()->playBackgroundMusic(str->getCString(), true);
	}
		
}
void CAudioManager::PlayerVoice(std::string voice)
{
	String*str = String::createWithFormat("Audio/%s.mp3", voice.c_str());
	SimpleAudioEngine::getInstance()->playEffect(str->getCString(), false);
}
void CAudioManager::PreLoadAudioBackground(std::string fileName)
{
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(fileName.c_str());
}
void CAudioManager::PreLoadAudio(const char* fileName)
{
	SimpleAudioEngine::getInstance()->preloadEffect(fileName);
}