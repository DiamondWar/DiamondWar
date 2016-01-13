#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "TowerItemUI.h"

using namespace cocos2d::ui;
class CChoseTowerUIManager :public cocos2d::Layer, public ChoseTowerDelegate, public TowerListDelegate
{
public:
	CREATE_FUNC(CChoseTowerUIManager);
	virtual bool init(); 
	static cocos2d::Scene* createScene();
	virtual void OnChoseTower(int index, bool flag);
	virtual void ClickTower(int index);
private:
	void OnStartButtonClickHandleEvent();
	Button* StartGame;
	const int Init_x = 380;
	const int Init_y = 700;
	cocos2d::Vector<CTowerItemUI*> ShowTowerList_;
};
