#pragma once
#include "cocos2d.h"
#include "AudioDelegate.h"
class CDuiHuaUIManager:public cocos2d::Node
{
public:
	CREATE_FUNC(CDuiHuaUIManager);
	CDuiHuaUIManager();
	~CDuiHuaUIManager();
	virtual bool init();
	virtual void update(float detal);
	void PlayPersonAudio(int index, float time,CAudioDelegate*delega);
private: 
	long long  startTime;
	long ContinueTime;
	CAudioDelegate* Delegate_;
	int Audio_Index;
};

