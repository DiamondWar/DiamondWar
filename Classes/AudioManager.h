#pragma once
#include "cocos2d.h"
class CAudioManager
{
public:
	CAudioManager();
	~CAudioManager();
	static CAudioManager* GetInstance();
	void PlayerBackGroundMusic(std::string music);
	void PlayerVoice(std::string voice);
	void PreLoadAudioBackground(std::string fileName);
	void UnLoadAudioBackground(std::string fileName);
	void PreLoadAudio(const char* fileName);
	void UnLoadAudio(const char* fileName);
private: 
	static CAudioManager* Instance_;
};

