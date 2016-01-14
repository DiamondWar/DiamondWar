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
	void SetIsChose(bool flag);
	void InitInfo(int index, int id, bool flag,bool isshow = true);
	int IconId;
	int Index;
	bool CanShow_ = true;
	bool CanChose_ = true;
	bool IsChosing_ = false;
	ChoseTowerDelegate* ChoseDelegate_;
	TowerListDelegate* TowerDelegate_;
	
private:
	cocos2d::Sprite* Icon_;
	cocos2d::Sprite* NoChoseSp_;
	cocos2d::Sprite* ChoseFlagSp_;

};

