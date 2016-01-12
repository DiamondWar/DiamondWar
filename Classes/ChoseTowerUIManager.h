#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"
using namespace cocos2d::ui;
class CChoseTowerUIManager:public cocos2d::Layer
{
public:
	CREATE_FUNC(CChoseTowerUIManager);
	virtual bool init(); 
	static cocos2d::Scene* createScene();
private:
	void OnStartButtonClickHandleEvent();
	Button* StartGame;
};
