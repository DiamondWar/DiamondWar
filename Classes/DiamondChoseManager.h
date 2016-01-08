#pragma once
#include "cocos2d.h"
#include "ShuiJingBase.h"

class CShuiJingChose
{
public:
	int Color;
	int Num;
	int indexlist[6];
};

class CDiamondChoseManager:public cocos2d::Node
{
public:
	CREATE_FUNC(CDiamondChoseManager);
	virtual bool init();
	virtual void update(float delta); 
	void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	bool CheckPointInThis(cocos2d::CCPoint pos);
	int CheckDiamondIsLoading();
	void SetCanShengChengShuiJing();
	CShuiJingChose* CanChoselist[4];
private: 
	void UpdateCanChoseShuiJing();
	cocos2d::Vector<CShuiJingBase*> SpriteList;
	cocos2d::Sprite* ChoseSprite_;
	
	const int init_x = 120;
	const int init_y = 15;
	int ChoseNum = 0;
	int StartIndex = 0;
	int LaseChoseColor = 0;
	int lastIndex = -1;
	int StartPoint = 0;
	int LastPoint = 0;
	bool IsAddOrDel = false;//判断方向 true是往前false是往后  0 是呆在1个格子中间
	
	int CurFrameCount = 0;
	int LastFrameCount = 0;
	bool  bIsCanShengChengShuiJing = true;
	int MaxLoadingTime = 180;
};

