#include "HurtShow.h"
USING_NS_CC;

CHurtShow::CHurtShow()
{
}
CHurtShow::~CHurtShow()
{
	SpriteArray.clear();

}
void CHurtShow::SetFont(int type)
{
	if (type == 1)
	{
		ResourceName = "bjz";
	}
	else if (type == 2)
	{
		ResourceName = "jxz";
	}
	else if (type == 3)
	{
		ResourceName = "pgz";
	}
	else if (type == 4)
	{
		ResourceName = "zdz";
	}
}
void CHurtShow::ShowLabel(int value, Node* node)
{
	int n = 0;
	while (value > 0)
	{
		int temp = value % 10;
		value = value / 10;

		CCString *string = CCString::createWithFormat("%s_%d.png", ResourceName, temp);
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(string->getCString());
		sprite->autorelease();
		SpriteArray.pushBack(sprite);
	}
	int count = SpriteArray.size();
	for (int i = 0; i < SpriteArray.size(); i++)
	{
		node->getParent()->addChild(SpriteArray.at(i));
		SpriteArray.at(i)->setPosition(node->getPosition().x + 40 / 2 * count - i * 40, node->getPosition().y);
	}
	isMove = true;
}
void CHurtShow::Update()
{
	if (isMove == true)
	{
		CCLOG("dddddddddddddddddddddddddddddddddddddddd");
		MoveNum++;
		for (int i = 0; i < SpriteArray.size(); i++)
		{
			SpriteArray.at(i)->setPosition(SpriteArray.at(i)->getPosition().x, SpriteArray.at(i)->getPosition().y + MoveNum);
		}
		if (MoveNum>10)
		{
			isMove = false;
			IsDelete_ = true;
			for (int i = 0; i < SpriteArray.size(); i++)
			{
				SpriteArray.at(i)->removeFromParent();
			}
			this->release();
		}

	}

}
