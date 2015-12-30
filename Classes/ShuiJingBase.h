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
	void ResetInfo( int Color,bool flag =true);
	int MyColor =0;
	bool IsLoading = false;//是否进入冷却
	bool IsCanChose_ = false;//是否可以选择
private: 
	cocos2d::CCProgressTimer* Progress_;
	cocos2d::CCSprite* MainSprite_;
	cocos2d::Label* CoolTimeLabel_;
	int  CoolTime = 0;
	const int MaxCoolTime = 300;
	bool IsTips_ = false;
	
};

