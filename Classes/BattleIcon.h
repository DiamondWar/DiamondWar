#pragma once
#include "cocos2d.h"
class BattleIcon:public cocos2d::Node
{
public:
	CREATE_FUNC(BattleIcon);
	BattleIcon();
	~BattleIcon();
	virtual bool init();
	void SetInfo(int id, int type,int color );
	void SetCanChose(bool flag);
private: 
	cocos2d::Sprite* Icon_;
	cocos2d::Label* IconNum_;
	cocos2d::Sprite* Bg_;
};

