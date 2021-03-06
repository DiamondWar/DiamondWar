#pragma once
#include "cocos2d.h"
#include "ui/UIButton.h"
#include "ui/UIScrollView.h"
#include "TowerItemUI.h"
#include "ui/UITextAtlas.h"

using namespace cocos2d::ui;
class CChoseTowerUIManager :public cocos2d::Layer, public ChoseTowerDelegate, public TowerListDelegate
{
public:
	CREATE_FUNC(CChoseTowerUIManager);
	virtual bool init(); 
	static cocos2d::Scene* createScene();
	virtual void onExit();
	virtual void OnChoseTower(int index, bool flag);
	virtual void ClickTower(int index);
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	void OnXinShouButtonClickHandleEvent();
	void OnStartButtonClickHandleEvent();
	void OnChoseTowerShowList(int index);
	Button* StartGame;
	ScrollView* ScrollView_;
	cocos2d::Sprite* ChoseTitleSp_;
	TextAtlas* ChoseTilteText_;
	cocos2d::Node*XinShouSp1;
	cocos2d::Node*XinshouSp2;
	cocos2d::Node*XinShouSp3;
	cocos2d::Node*XinShouSp4;
	cocos2d::Node*XinShouSp5;
	cocos2d::Node*XinShouSp6;
	Button*XinShouButton_;
	const int Init_x = 380;
	const int Init_y = 820;
	cocos2d::Vector<CTowerItemUI*> ShowTowerList_;
	int TypeList[4];
	cocos2d::Vector<CTowerItemUI*> CanChoseItemList_[20];
	int CurChoseIndex_ = 0;//当前选择的对象下标

	int xinshouNum = 0;
};
