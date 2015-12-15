#include "DiamondChoseManager.h"
#include "ShuiJingBase.h"
#include "BattleUIManager.h"
#include "GameSceneControl.h"
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
	int nw = 1300;
	int nh = 185;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		int x = pt.x - init_x;
		int index = x / 170;
		if (index >= 7)
			index = 6;
		if (SpriteList.at(index)->IsLoading == false)
		{
			LaseChoseColor = SpriteList.at(index)->MyColor;
			lastIndex = index;
			StartIndex = index;
			ChoseNum = 1;
			StartPoint = SpriteList.at(index)->getPosition().x+50;
			LastPoint = StartPoint;
			ChoseSprite_->setAnchorPoint(ccp(0, 0));
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
	int nw = 1300;
	int nh = 185;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		int x = pt.x - init_x;
		int index = x / 170;
		if (index >= 7)
			index = 6;
		if (lastIndex + 1 == index )
		{
			if ((LaseChoseColor == SpriteList.at(index)->MyColor ||LaseChoseColor==5|| SpriteList.at(index)->MyColor == 5) && SpriteList.at(index)->IsLoading == false)
			{
				if (LaseChoseColor == 5 && ChoseNum == 1)
					LaseChoseColor = SpriteList.at(index)->MyColor;
				if (ChoseNum == 1)
				{
					IsAddOrDel = true;//判断刚开始是从左往右选的
				}
				if (IsAddOrDel == true)
				{
					ChoseNum++;
				}
				else
				{
					ChoseNum--; 
					if (ChoseNum <= 0)
					{
						ChoseNum = 2;
						IsAddOrDel = true;
					}

				}
				
				lastIndex = index;
				int len = abs(pt.x - StartPoint);
				if (pt.x < StartPoint)
				{
					ChoseSprite_->setAnchorPoint(ccp(1, 0));
				}
				else
				{
					ChoseSprite_->setAnchorPoint(ccp(0, 0));
				}
				ChoseSprite_->setScaleX((float)len / 256.0f);
			}
			else
			{
				//上一个选择的颜色跟这次的不一样，不再进行连线
			}
		}
		else if (lastIndex - 1 == index)
		{
			if ((LaseChoseColor == SpriteList.at(index)->MyColor || LaseChoseColor == 5 || SpriteList.at(index)->MyColor == 5) && SpriteList.at(index)->IsLoading == false)
			{
				if (LaseChoseColor == 5 && ChoseNum == 1)
					LaseChoseColor = SpriteList.at(index)->MyColor;
				if (ChoseNum == 1)
				{
					IsAddOrDel = false;
				}
				if (IsAddOrDel == true)
				{
					ChoseNum--;
					if (ChoseNum <= 0)
					{
						ChoseNum = 2;
						IsAddOrDel = false;
						
					}
				}
				else
				{
					ChoseNum++;	
					lastIndex = index;
				}
				lastIndex = index;
				int len = abs(pt.x - StartPoint);
				if (pt.x < StartPoint)
				{
					ChoseSprite_->setAnchorPoint(ccp(1, 0));
				}
				else
				{
					ChoseSprite_->setAnchorPoint(ccp(0, 0));
				}
				ChoseSprite_->setScaleX((float)len / 256.0f);
			}
			else
			{
				
				//上一个选择的颜色跟这次的不一样，不再进行连线
			}
		}
		else if (lastIndex==index)
		{
			if (ChoseNum == 1 && SpriteList.at(lastIndex)->MyColor == 5)
				LaseChoseColor = SpriteList.at(index)->MyColor;
			int len = abs(pt.x - StartPoint);
			if (pt.x < StartPoint)
			{
				ChoseSprite_->setAnchorPoint(ccp(1, 0));
			}
			else
			{
				ChoseSprite_->setAnchorPoint(ccp(0, 0));
			}
			ChoseSprite_->setScaleX((float)len / 256.0f);

		}
		CCLOG("ChoseNum ==%d, LastChoseColor==%d, LastIndex== %d, Index== %d", ChoseNum, LaseChoseColor, lastIndex, index);
		
	}
	if (lastIndex >= 0)
	{
		int last = lastIndex;
		int start = StartIndex;
		int temp = start > last ? last : start;
		if (temp == last)
			last = start;
		for (int i = 0; i < SpriteList.size(); i++)
		{
			if (i >= temp&&i <= last)
			SpriteList.at(i)->setPositionY(pt.y - 80);
			else 
				SpriteList.at(i)->setPositionY(init_y);

		}
		ChoseSprite_->setPositionY(pt.y - 80);
	}
}
//触摸事件结束，也就是手指松开时  
void CDiamondChoseManager::onTouchEnded(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = 1300;
	int nh = 185;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		CCLOG("onTouchEnded   = %f,%f", pt.x, pt.y);
		ChoseSprite_->setScaleX(0);
		for (int i = 0; i < SpriteList.size(); i++)
		{
			SpriteList.at(i)->setPosition(init_x + 170 * i, init_y);
		}
		lastIndex = -1;
	}
	else
	{
		if (pt.y > nh)
		{
			if (lastIndex != -1)
			{
				ChoseSprite_->setScaleX(0);
				
				//结算当前消耗的 如果阵容中有消耗的颜色水晶 则出兵 否则就消耗到彩色水晶里面
				CBattleUIManager* manager = static_cast<CBattleUIManager*>(this->getParent());
				bool flag = false;
				if (!CGameSceneControl::GetInstance()->IsHaveConsumeHero(LaseChoseColor, ChoseNum))
				{
					flag = true; 
					manager->UpdateCaiSeShuiJing(ChoseNum);
				}
				int temp = StartIndex > lastIndex ? lastIndex : StartIndex;
				for (int i = 0; i < ChoseNum; i++)
				{
					int rand = random(1, 4);
					SpriteList.at(temp)->ResetInfo(rand);
					if (flag == true)
					manager->CreateMoveAnimation(LaseChoseColor, ccp(SpriteList.at(temp)->getPositionX() + getPositionX(), SpriteList.at(temp)->getPositionY()), ccp(Director::getInstance()->getWinSize().width-80,90));
					else 
						manager->CreateMoveAnimation(LaseChoseColor, ccp(SpriteList.at(temp)->getPositionX() + getPositionX(), SpriteList.at(temp)->getPositionY()), ccp(200, 540));
					SpriteList.pushBack(SpriteList.at(temp));
					SpriteList.erase(temp);
					
				}
				for (int i = 0; i < SpriteList.size(); i++)
				{
					SpriteList.at(i)->setPosition(init_x + 170 * i, init_y);
				}
				lastIndex = -1;
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

bool CDiamondChoseManager::CheckPointInThis(CCPoint pos)
{
	int x = getPositionX();
	int index = (pos.x - x - init_x) / 170;

	if (index <= 6&&pos.y<180&&SpriteList.at(index)->IsLoading == false)
	{
		SpriteList.at(index)->ResetInfo(5,false);
		return true;
	}
	return false;
}

