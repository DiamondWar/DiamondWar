#pragma once

#ifndef _CSOLIDERDIE_H_
#define  _CSOLIDERDIE_H_
#include "cocos2d.h"
class CSoliderDie :public cocos2d::Node
{
public:
	CSoliderDie();
	~CSoliderDie();
	void ShowLabel(int value,Node* node);
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
