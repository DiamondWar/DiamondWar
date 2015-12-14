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
	//�ҷ�����Ѫ����ʾ
	cocos2d::Sprite* MyIcon_;
	cocos2d::Label* MyName_;
	cocos2d::Label* MyBloodDesc_;
	cocos2d::CCProgressTimer* MyBloodProgress_;
	//�ط�Ѫ����ʾ
	cocos2d::Sprite* SecondIcon_;
	cocos2d::Label* SecondName_;
	cocos2d::Label* SecondBloodDesc_;
	cocos2d::CCProgressTimer* SecondBloodProgress_;
	//��ɫˮ����ʾ
	cocos2d::Sprite* CaiSeShuiJing_;
	cocos2d::Label* CaiSeShuiJingLabel_;
	float CurCaiSeShuiJingPrecentNum_;
	cocos2d::Node* CaiseShuiJingRoot_;
	bool IsChoseCaiSe_ = false;//֮ǰ�Ƿ�㵽��ɫˮ��
	bool IsCanChoseCaiSe_ = false;//�Ƿ����ʹ�ò�ɫˮ��
};

