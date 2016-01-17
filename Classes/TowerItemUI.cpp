#include "TowerItemUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
bool CTowerItemUI::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto* node = CSLoader::createNode("IconItem.csb");
	Icon_ = static_cast<Sprite*>(node->getChildByName("Sprite"));
	NoChoseSp_ = static_cast<Sprite*>(node->getChildByName("NoAdd"));
	ChoseFlagSp_ = static_cast<Sprite*>(node->getChildByName("ChoseStatus"));
	ChoseFlagSp_->setVisible(IsChosing_);
	addChild(node);
	setContentSize(Icon_->getContentSize());
	
	return true;
}
void CTowerItemUI::InitInfo(int index, int id, bool flag, bool isshow)
{
	Index = index;
	CanChose_ = flag;
	CanShow_ = isshow;
	SetInfo(id);
	SetCanChose(flag);
}
void CTowerItemUI::SetInfo(int id)
{

	IconId = id;
	if (id >=1000)
	{
		String*str = String::createWithFormat("texture_hero_%d.png" ,id);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		Icon_->setSpriteFrame(frame);
		Icon_->setVisible(true);
	}
	else if (id > 0)
	{
		String*str = String::createWithFormat("texture_spell_%d.png", id);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		Icon_->setSpriteFrame(frame);
		Icon_->setVisible(true);
	}
	else
	{
		Icon_->setVisible(false);
	}
	
	
}
void CTowerItemUI::SetCanChose(bool flag)
{
	CanChose_ = flag;
	NoChoseSp_->setVisible(!flag);
}
void CTowerItemUI::SetIsChose(bool flag)
{
	IsChosing_ = flag;
	ChoseFlagSp_->setVisible(IsChosing_);
}
