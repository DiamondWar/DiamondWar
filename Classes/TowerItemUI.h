#pragma once
#include "cocos2d.h"
class CTowerItemUI:public cocos2d::Node
{
public:
	CREATE_FUNC(CTowerItemUI);
	virtual bool init();
	void SetInfo(int id,bool flag);
};

