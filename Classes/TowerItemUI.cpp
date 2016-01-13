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
//�����¼���ʼ����ָ����ʱ  
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
//�����ƶ��¼���Ҳ������ָ����Ļ�����Ĺ���  
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
//�����¼�������Ҳ������ָ�ɿ�ʱ  
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
//��ϴ����¼���һ����ϵͳ�㼶����Ϣ�������绰�������¼��ͻᱻ���  
void CTowerItemUI::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}