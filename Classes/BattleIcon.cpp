#include "BattleIcon.h"
USING_NS_CC;

BattleIcon::BattleIcon()
{
}


BattleIcon::~BattleIcon()
{
}
bool BattleIcon::init()
{
	if (!Node::init())
	{
		return false;
	}
	/*Bg_ = Sprite::createWithSpriteFrameName("iconbg.png");
	setContentSize(Bg_->getContentSize());
	addChild(Bg_);*/
	return true;
}
void BattleIcon::SetInfo(int id, int type,int color )
{

	String* string = String::createWithFormat("icon%d.png", id);
	Icon_ = CCSprite::createWithSpriteFrameName(string->getCString());
	addChild(Icon_);
	setContentSize(Icon_->getContentSize());
	TTFConfig config("fonts/ERASDEMI.TTF", 25);
	String* strtype  = String::createWithFormat("%d", type);
	IconNum_ = Label::createWithTTF(config, strtype->getCString(),TextHAlignment::LEFT);
	IconNum_->setAnchorPoint(Vec2(0, 0));
	IconNum_->setPosition(-35, 15);
	switch (color+1)
	{
	case 1:
		IconNum_->setColor(Color3B::YELLOW);
		break;
	case 2:
		IconNum_->setColor(Color3B::GREEN);
		break;
	case 3:
		IconNum_->setColor(Color3B::BLUE);
		break;
	case 4:
		IconNum_->setColor(Color3B::MAGENTA);
		break;
	default:
		break;
	}
	addChild(IconNum_);
	

}
