#pragma once
#include "cocos2d.h"
#include "ui/UIVideoPlayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
using namespace  cocos2d::experimental::ui;
#endif
class CVideoSceneManager:public cocos2d::Layer
{
public:
	CREATE_FUNC(CVideoSceneManager);
	CVideoSceneManager();
	~CVideoSceneManager();
	virtual bool init();
	virtual void onEnter();
	static cocos2d::Scene* createScene();
private:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	cocos2d::experimental::ui::VideoPlayer* videoPlayer;
	void videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);
#endif
	void showVideo(const char* name);
	void videoPlayOverCallBack();
};

