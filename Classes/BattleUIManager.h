#pragma once
#include "cocos2d.h"
#include "DiamondChoseManager.h"
#include "ui/UILoadingBar.h"
#include "ui/UITextAtlas.h"
using namespace cocos2d::ui;
class CBattleUIManager :
	public cocos2d::Node
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
	void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::Node* CaiseShuiJingRoot_;
private: 
	CDiamondChoseManager * DiamondManger;
	//�ҷ�����Ѫ����ʾ
	LoadingBar* MyBloodProgress_;
	//�ط�Ѫ����ʾ
	LoadingBar* SecondBloodProgress_;
	//��ɫˮ����ʾ
	cocos2d::Sprite* CaiSeShuiJing_;
	float CurCaiSeShuiJingPrecentNum_;
	//ʱ����ʾ
	cocos2d::Vector<cocos2d::Sprite*> TimeList_;
	TextAtlas * CaiSeShuiJingTimeLabel_;
	bool IsChoseCaiSe_ = false;//֮ǰ�Ƿ�㵽��ɫˮ��
	bool IsCanChoseCaiSe_ = false;//�Ƿ����ʹ�ò�ɫˮ��
	bool IsMoveChoseCaiSe_ = false;
	float DetiaTime = 0;
	float MaxTime = 600;
};

