#pragma once
#include "cocos2d.h"
#include "DiamondChoseManager.h"
#include "ui/UILoadingBar.h"
#include "ui/UITextAtlas.h"
#include "AudioDelegate.h"
using namespace cocos2d::ui;
class CBattleUIManager :
	public cocos2d::Node,public CAudioDelegate
{
public:
	CREATE_FUNC(CBattleUIManager);
	virtual bool init();
	virtual void update(float delta);
	void CreateTime();
	void ShowTime();
	void CreateCaiSeShuiJing();
	void UpdateCaiSeShuiJing(int num);
	void CreateMoveAnimation(int color ,cocos2d::CCPoint start, cocos2d::CCPoint target);
	void OnMoveAnimationComplete(cocos2d::CCSprite* spr);
	virtual void OnAudioComplete(int index);
	void OnPlayVoice(int index, float time);
	void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	//主角1头像播放动画
	void Role1PlayAnimation(int index);
	//主角1头像播放动画
	void Role2PlayAnimation(int index);
	cocos2d::Node* CaiseShuiJingRoot_;
private: 
	

	CDiamondChoseManager * DiamondManger;
	//我方基地头像
	cocos2d::Sprite*  MyIcon_;
	cocos2d::Sprite* MyDuiHuaSp_;
	//地方基地头像
	cocos2d::Sprite* SecondIcon_;
	cocos2d::Sprite* SecondDuiHuaSp_;
	//我方基地血条显示
	LoadingBar* MyBloodProgress_;
	//地方血条显示
	LoadingBar* SecondBloodProgress_;
	//彩色水晶显示
	cocos2d::Sprite* CaiSeShuiJing_;
	float CurCaiSeShuiJingPrecentNum_;
	//时间显示
	cocos2d::Vector<cocos2d::Sprite*> TimeList_;
	TextAtlas * CaiSeShuiJingTimeLabel_;
	bool IsChoseCaiSe_ = false;//之前是否点到彩色水晶
	bool IsCanChoseCaiSe_ = false;//是否可以使用彩色水晶
	bool IsMoveChoseCaiSe_ = false;
	float DetiaTime = 0;
	float MaxTime = 600;
};

