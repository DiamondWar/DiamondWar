#pragma once

#ifndef _CHURTSHOW_H_
#define  _CHURTSHOW_H_
#include "cocos2d.h"
#include "Solider.h"
class CHurtShow :public cocos2d::Node
{
public:
	CHurtShow();
	~CHurtShow();
	void ShowLabel(int value,CSolider* node);
	void SetFont(int type);
    void Update();
	bool IsDelete_ = false;
private: 
	char* ResourceName;
	cocos2d::Vector<cocos2d::CCSprite*> SpriteArray;
	bool isMove = false;
	int MoveNum = 0;
};
#endif
