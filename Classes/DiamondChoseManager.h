#pragma once
#include "cocos2d.h"
#include "ShuiJingBase.h"

class CDiamondChoseManager:public cocos2d::Node
{
public:
	CREATE_FUNC(CDiamondChoseManager);
	virtual bool init();

	void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private: 
	cocos2d::Vector<CShuiJingBase*> SpriteList;

	cocos2d::Sprite* ChoseSprite_;
	const int init_x = 30;
	const int init_y = 15;
	int ChoseNum = 0;
	int StartIndex = 0;
	int LaseChoseColor = 0;
	int lastIndex = 0;
	int StartPoint = 0;
};

