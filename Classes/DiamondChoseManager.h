#pragma once
#include "cocos2d.h"
class CDiamondChoseManager:public cocos2d::Node
{
public:
	CREATE_FUNC(CDiamondChoseManager);
	virtual bool init();

private: 
	cocos2d::Vector<cocos2d::Node*> SpriteList;
};

