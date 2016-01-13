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
	addChild(node);
	setContentSize(Icon_->getContentSize());
	EventListenerTouchOneByOne*	 listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [this](Touch* touch, Event* event)
	{
		onTouchBegan(touch, event);
		return true;
	};
	listener->onTouchMoved = [this](Touch* touch, Event* event)
	{
		onTouchMoved(touch, event);
	};
	listener->onTouchEnded = [this](Touch* touch, Event* event)
	{
		touch->setTouchInfo(1, 750, 50);
		onTouchEnded(touch, event);
	};
	listener->onTouchCancelled = [this](Touch* touch, Event* event)
	{
		onTouchCancelled(touch, event);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
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
	if (id != 0)
	{
		String*str = String::createWithFormat("texture_hero_%d" ,id);
		SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
		Icon_->setSpriteFrame(frame);

	}
	else
	{
		Icon_->setVisible(false);
	}
	
	
}
void CTowerItemUI::SetCanChose(bool flag)
{
	NoChoseSp_->setVisible(!flag);
}
//触摸事件开始，手指按下时  
void CTowerItemUI::onTouchBegan(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
	}

}
//触摸移动事件，也就是手指在屏幕滑动的过程  
void CTowerItemUI::onTouchMoved(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		
	}

}
//触摸事件结束，也就是手指松开时  
void CTowerItemUI::onTouchEnded(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		if (IconId != 0)
		{
			if (ChoseDelegate_ != nullptr)
				ChoseDelegate_->OnChoseTower(Index, true);
			if (TowerDelegate_ != nullptr)
				TowerDelegate_->ClickTower(Index);
		}
	}

}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断  
void CTowerItemUI::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}