#pragma once
#include "cocos2d.h"
class CShuiJingBase:public cocos2d::Node
{
public:
	CREATE_FUNC(CShuiJingBase);
	virtual bool init();
	virtual void  update(float dt);
	void SetInfo(int index);
private: 
	cocos2d::CCProgressTimer* Progress_;
	cocos2d::CCSprite* Lock_;
	cocos2d::CCSprite* MainSprite_;
};

