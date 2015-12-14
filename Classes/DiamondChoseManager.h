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
	bool CheckPointInThis(cocos2d::CCPoint pos);
private: 
	cocos2d::Vector<CShuiJingBase*> SpriteList;
	cocos2d::Sprite* ChoseSprite_;
	
	const int init_x = 30;
	const int init_y = 15;
	int ChoseNum = 0;
	int StartIndex = 0;
	int LaseChoseColor = 0;
	int lastIndex = -1;
	int StartPoint = 0;
	int LastPoint = 0;
	bool IsAddOrDel = false;//判断方向 true是往前false是往后  0 是呆在1个格子中间
	
};

