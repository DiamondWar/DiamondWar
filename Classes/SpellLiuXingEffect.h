#pragma once
#include "cocos2d.h"
class CSpellLiuXingEffect :public cocos2d::Node
{
public:
	CREATE_FUNC(CSpellLiuXingEffect);
	virtual bool init();
	virtual void update(float delta);
	CSpellLiuXingEffect();
	~CSpellLiuXingEffect();
};
