#pragma once
#include "cocos2d.h"
#include "AudioDelegate.h"
class CTowerItemUI:public cocos2d::Node
{
public:
	CREATE_FUNC(CTowerItemUI);
	virtual bool init();
	void SetInfo(int id);
	void SetCanChose(bool flag);
	void InitInfo(int index, int id, bool flag,bool isshow = true);
	int IconId;
	int Index;
	bool CanShow_;
	bool CanChose_;
	ChoseTowerDelegate* ChoseDelegate_;
	TowerListDelegate* TowerDelegate_;
	void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	cocos2d::Sprite* Icon_;
	cocos2d::Sprite* NoChoseSp_;

};

