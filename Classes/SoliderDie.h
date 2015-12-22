#pragma once

#ifndef _CSOLIDERDIE_H_
#define  _CSOLIDERDIE_H_
#include "cocos2d.h"
#include "Solider.h"
class CSoliderDie :public cocos2d::Node
{
public:
	CSoliderDie();
	~CSoliderDie();
	void ShowLabel(int value,CSolider* node);
	void SetFont(int type);
    void Update();
	bool IsDelete_ = false;
private: 
	char* ResourceName;
	cocos2d::Sprite* Sprite_;
	bool isMove = false;
	int MoveNum = 0;
};
#endif
