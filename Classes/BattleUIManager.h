#pragma once
#include "cocos2d.h"
#include "BattleIcon.h"
#include "DiamondChoseManager.h"
class CBattleUIManager :
	public cocos2d::Node
{
public:
	CREATE_FUNC(CBattleUIManager);
	virtual bool init();
	virtual void update(float delta);
	void CreateFirstBase();
	void CreateSecondBase();
	void CreateCaiSeShuiJing();
	void UpdateCaiSeShuiJing(int num);
	void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private: 
	cocos2d::Vector<BattleIcon*> IconList;
	CDiamondChoseManager * DiamondManger;
	//我方基地血条显示
	cocos2d::Sprite* MyIcon_;
	cocos2d::Label* MyName_;
	cocos2d::Label* MyBloodDesc_;
	cocos2d::CCProgressTimer* MyBloodProgress_;
	//地方血条显示
	cocos2d::Sprite* SecondIcon_;
	cocos2d::Label* SecondName_;
	cocos2d::Label* SecondBloodDesc_;
	cocos2d::CCProgressTimer* SecondBloodProgress_;
	//彩色水晶显示
	cocos2d::Sprite* CaiSeShuiJing_;
	cocos2d::Label* CaiSeShuiJingLabel_;
	float CurCaiSeShuiJingPrecentNum_;
	cocos2d::Node* CaiseShuiJingRoot_;
	bool IsChoseCaiSe_ = false;//之前是否点到彩色水晶
	bool IsCanChoseCaiSe_ = false;//是否可以使用彩色水晶
};

