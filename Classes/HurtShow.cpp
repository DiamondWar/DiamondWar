#include "HurtShow.h"
#include "CGlobleConfig.h"
#include "GameSceneControl.h"
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
void CHurtShow::ShowLabel(int value, CSolider* node)
{
	int n = 0;
	if (value == 0)
	{
		IsDelete_ = true;
		return;
	}
	while (value > 0)
	{
		int temp = value % 10;
		value = value / 10;

		CCString *string = CCString::createWithFormat("%s_%d.png", ResourceName, temp);
		CCSprite* sprite = CCSprite::createWithSpriteFrameName(string->getCString());
		sprite->autorelease();
		SpriteArray.pushBack(sprite);
	}
	CCString *string1 = CCString::createWithFormat("%s_10.png", ResourceName);
	CCSprite* sprite1 = CCSprite::createWithSpriteFrameName(string1->getCString());
	sprite1->autorelease();
	SpriteArray.pushBack(sprite1);

	int count = SpriteArray.size();
	for (int i = 0; i < SpriteArray.size(); i++)
	{
		CGameSceneControl::GetInstance()->GameRoot_->addChild(SpriteArray.at(i));
		SpriteArray.at(i)->setPosition(node->CenterPoint_->getPosition().x+node->Obj->getPosition().x + 40 / 2 * count - i * 40, node->Obj->getPosition().y+node->CenterPoint_->getPosition().y);
	}
	isMove = true;
}
void CHurtShow::Update()
{
	if (CCGlobleConfig::Game_time % 3 == 0)
	{
		if (isMove == true)
		{
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


}
