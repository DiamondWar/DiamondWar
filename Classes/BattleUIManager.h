#pragma once
#include "cocos2d.h"
#include "BattleIcon.h"
class CBattleUIManager :
	public cocos2d::Node
{
public:
	CREATE_FUNC(CBattleUIManager);
	virtual bool init();
	virtual void update(float delta);
	void CreateFirstBase();
	void CreateSecondBase();
private: 
	cocos2d::Vector<BattleIcon*> IconList;

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
};

