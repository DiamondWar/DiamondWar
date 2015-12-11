#include "DiamondChoseManager.h"
#include "ShuiJingBase.h"
USING_NS_CC;

bool CDiamondChoseManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	for (int i = 0; i < 7;i++)
	{
		int rand = random(1,4);
		String* string = String::createWithFormat("shujing_%d.png", rand);
		CShuiJingBase* sprite = CShuiJingBase::create();
		sprite->SetInfo(rand);
		sprite->setAnchorPoint(Vec2(0,0));
		sprite->setPosition(-580+170 * i, 15);
		addChild(sprite);
		SpriteList.pushBack(sprite);
	}
	return true;
}

