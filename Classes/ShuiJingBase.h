#pragma once
#include "cocos2d.h"
class CShuiJingBase:public cocos2d::Node
{
public:
	CREATE_FUNC(CShuiJingBase);
	virtual bool init();
	virtual void  update(float dt);
	void SetInfo(int index,bool flag);
	void SetTipsInfo(bool flag);
	void SetCanExist(bool flag = true);
	void ResetInfo(int num,int Color, bool flag = true);
	void SetShuiJingCanLoading(int cooltime);
	void SetShuiJingLoadComplete();
	int GetCurCoolTime();
	int MyColor =0;
	bool IsLoading = false;//是否进入冷却
	bool IsCanChose_ = false;//是否可以选择
	bool IsCanLoading_ = false;
private: 
	cocos2d::CCProgressTimer* Progress_;
	cocos2d::CCSprite* MainSprite_;
	cocos2d::CCSprite*AnimationSp_;
	cocos2d::Sprite* TimeSp_;
	const int MaxCoolTime = 180;
	int  CurMaxCoolTime = 0;
	bool IsTips_ = false;
	
};

