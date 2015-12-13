#include "DiamondChoseManager.h"
#include "ShuiJingBase.h"

USING_NS_CC;

bool CDiamondChoseManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	setContentSize(Size(1300, 185));
	for (int i = 0; i < 7;i++)
	{
		int rand = random(1,4);
		String* string = String::createWithFormat("shujing_%d.png", rand);
		CShuiJingBase* sprite = CShuiJingBase::create();
		sprite->SetInfo(rand);
		sprite->setAnchorPoint(Vec2(0,0));
		sprite->setPosition(init_x + 170 * i, init_y);
		addChild(sprite);
		SpriteList.pushBack(sprite);
	}
	ChoseSprite_ = Sprite::createWithSpriteFrameName("line_1.png");
	Vector<SpriteFrame*> vsp;
	for (int i = 1; i <= 10; i++)
	{
		String *string = String::createWithFormat("line_%d.png", i);
		SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
		vsp.pushBack(spfr);
	}
	Animation* animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
	Animate *animate = Animate::create(animation);
	auto *ac1 = RepeatForever::create(animate);
	ChoseSprite_->runAction(ac1);
	addChild(ChoseSprite_);
	ChoseSprite_->setAnchorPoint(Vec2(0, 0));
	ChoseSprite_->setPosition(90, init_y);
	ChoseSprite_->setScaleX(0);
	ChoseSprite_->setScaleY(3);
	ChoseSprite_->setVisible(true);

	
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
		///touch->setTouchInfo(1, 750, 50);
		onTouchEnded(touch, event);
	};
	listener->onTouchCancelled = [this](Touch* touch, Event* event)
	{
		onTouchCancelled(touch, event);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
//触摸事件开始，手指按下时  
void CDiamondChoseManager::onTouchBegan(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		int x = pt.x - init_x;
		int index = x / 170;
		if (SpriteList.at(index)->IsLoading == false)
		{
			LaseChoseColor = SpriteList.at(index)->MyColor;
			lastIndex = index;
			StartIndex = index;
			ChoseNum = 1;
			StartPoint = SpriteList.at(index)->getPosition().x;
			ChoseSprite_->setPositionX(StartPoint);
		}
		else
		{
			LaseChoseColor = 0;
			lastIndex = -1;
			StartIndex = -1;
			ChoseNum = 0;
		}
	
		//CCLOG("ChoseNum ==%d, LastChoseColor==%d, LastIndex== %d, Index== %d", ChoseNum, LaseChoseColor, lastIndex, index);
	}
	
}
//触摸移动事件，也就是手指在屏幕滑动的过程  
void CDiamondChoseManager::onTouchMoved(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		int x = pt.x - init_x;
		int index = x / 170;
		if (index >= 7)
			index = 6;
		if (lastIndex + 1 == index || lastIndex - 1 == index)
		{
			if (LaseChoseColor == SpriteList.at(index)->MyColor&&SpriteList.at(index)->IsLoading == false)
			{
				ChoseNum++;
				lastIndex = index;
				int len = abs(pt.x - StartPoint);
				ChoseSprite_->setScaleX((float)len / 256.0f);
			}
			else
			{
				//上一个选择的颜色跟这次的不一样，不再进行连线
			}
		}
		else if (lastIndex==index)
		{
			int len = abs(pt.x - StartPoint);
			ChoseSprite_->setScaleX((float)len / 256.0f);

		}
		
		
		//CCLOG("ChoseNum ==%d, LastChoseColor==%d, LastIndex== %d, Index== %d", ChoseNum, LaseChoseColor, lastIndex, index);
	}
	if (lastIndex >= 0)
	{
		int temp = StartIndex > lastIndex ? lastIndex : StartIndex;
		if (temp == lastIndex)
			lastIndex = StartIndex;
		for (int i = temp; i <= lastIndex; i++)
		{
			SpriteList.at(i)->setPositionY(pt.y - 80);

		}
		ChoseSprite_->setPositionY(pt.y - 80);
	}
	
}
//触摸事件结束，也就是手指松开时  
void CDiamondChoseManager::onTouchEnded(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		CCLOG("onTouchEnded   = %f,%f", pt.x, pt.y);
		ChoseSprite_->setScaleX(0);
		for (int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList.at(i)->setPosition(init_x + 170 * i, init_y);
		}
	}
	else
	{
		if (pt.y > nh)
		{
			if (lastIndex != -1)
			{
				ChoseSprite_->setScaleX(0);
				//结算当前消耗的
				int temp = StartIndex > lastIndex ? lastIndex : StartIndex;
				for (int i = 0; i < ChoseNum; i++)
				{
					int rand = random(1, 4);
					SpriteList.at(temp)->ResetInfo(rand);
					SpriteList.pushBack(SpriteList.at(temp));
					SpriteList.erase(temp);

				}
				for (int i = 0; i < SpriteList.size(); i++)
				{
					SpriteList.at(i)->setPosition(init_x + 170 * i, init_y);
				}
			}
		
		}
		else
		{
			ChoseSprite_->setScaleX(0);
		}
	}

}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断  
void CDiamondChoseManager::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}

