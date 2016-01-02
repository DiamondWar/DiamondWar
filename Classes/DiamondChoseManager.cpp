#include "DiamondChoseManager.h"
#include "ShuiJingBase.h"
#include "BattleUIManager.h"
#include "GameSceneControl.h"
#include "CGlobleConfig.h"
#include "SoliderConfig.h"
#include "SpellConfig.h"
USING_NS_CC;

bool CDiamondChoseManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	for (int i = 0; i < 4;i++)
	{
		Animation* animation = NULL;
		String* str = String::createWithFormat("ShuiJing_%d", i+1);
		animation = AnimationCache::sharedAnimationCache()->getAnimation(str->getCString());
		if (animation == NULL)
		{
			Vector<SpriteFrame*> vsp;
			for (int n = 1; n <= 9;n++)
			{
				String *string = String::createWithFormat("UI_crystal_shuijing_%d_%d.png",i+1 , n);
				SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
				vsp.pushBack(spfr);
			}
			animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
			AnimationCache::sharedAnimationCache()->addAnimation(animation, str->getCString());
		}
	}
	
	for (int i = 0; i < 4;i++)
	{
		CShuiJingChose *chose = new CShuiJingChose();
		chose->Color = 1+i;
		chose->indexlist[0] = 0 ;
		chose->indexlist[1] =  0 ;
		chose->indexlist[2] =  0;
		chose->indexlist[3] =  0 ;
		chose->indexlist[4] =  0 ;
		chose->indexlist[5] =  0 ;
		chose->Num = 0;
		CanChoselist[i] = chose;
	}
	setContentSize(Size(1300, 185));
	for (int i = 0; i < 7;i++)
	{
		int rand = random(1,4);
		CShuiJingBase* sprite = CShuiJingBase::create();
		sprite->SetInfo(rand,i!=7);
		sprite->setAnchorPoint(Vec2(0,0));
		sprite->setPosition(init_x + 170 * i, init_y);
		addChild(sprite);
		if (i<=5)
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
	UpdateCanChoseShuiJing();
	return true;
}
void CDiamondChoseManager::UpdateCanChoseShuiJing()
{
	for (int i = 0; i < 7; i++)
	{
		CShuiJingBase* base = SpriteList.at(i);
		if (base->IsLoading == false && base->IsCanChose_ == true)
		{
			CanChoselist[base->MyColor - 1]->indexlist[CanChoselist[base->MyColor - 1]->Num] = i;
			if (CanChoselist[base->MyColor - 1]->Num != 0)
			{
				if (CanChoselist[base->MyColor - 1]->indexlist[CanChoselist[base->MyColor - 1]->Num - 1] == i - 1)
				{
					CanChoselist[base->MyColor - 1]->Num++;
				}
				else
				{
					CanChoselist[base->MyColor - 1]->indexlist[CanChoselist[base->MyColor - 1]->Num] = 0;
				}
			}
			else
			{
				CanChoselist[base->MyColor - 1]->Num++;
			}
		}
		base->SetTipsInfo(false);
	}
	for (int i = 0; i < 4;i++)
	{
		int index = CGameSceneControl::GetInstance()->IsHaveHero(CanChoselist[i]->Color, CanChoselist[i]->Num);
		if (index != -1)
		{
			if (index < 6)
			{
				CSoliderData* data = CSoliderConfig::GetInstance()->GetItemById(CGameSceneControl::GetInstance()->HeroList[index]);
				int num = data->NeedStar;
				for (int n = 0; n < num; n++)
				{
					SpriteList.at(CanChoselist[i]->indexlist[n])->SetTipsInfo(true);
				}
			}
			else
			{
				CSpellData* data = CSpellConfig::GetInstance()->GetItemById(CGameSceneControl::GetInstance()->HeroList[index]);
				int num = data->NeedStar_;
				for (int n = 0; n < num; n++)
				{
					SpriteList.at(CanChoselist[i]->indexlist[n])->SetTipsInfo(true);
				}
				
			}
			
		}
	}
}
void CDiamondChoseManager::update(float delta)
{
	if (CCGlobleConfig::Game_time % 10 == 0)
	{
		
	}
}
//�����¼���ʼ����ָ����ʱ  
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
//�����ƶ��¼���Ҳ������ָ����Ļ�����Ĺ���  
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
			if ((LaseChoseColor == SpriteList.at(index)->MyColor || LaseChoseColor == 5 || SpriteList.at(index)->MyColor == 5) && SpriteList.at(index)->IsLoading == false && SpriteList.at(index)->IsCanChose_ == true)
			{
				if (LaseChoseColor == 5 && ChoseNum == 1)
					LaseChoseColor = SpriteList.at(index)->MyColor;
				if (ChoseNum == 1)
				{
					IsAddOrDel = true;//�жϸտ�ʼ�Ǵ�������ѡ��
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
				//��һ��ѡ�����ɫ����εĲ�һ�������ٽ�������
			}
		}
		else if (lastIndex - 1 == index)
		{
			if ((LaseChoseColor == SpriteList.at(index)->MyColor || LaseChoseColor == 5 || SpriteList.at(index)->MyColor == 5) && SpriteList.at(index)->IsLoading == false && SpriteList.at(index)->IsCanChose_ == true)
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
				
				//��һ��ѡ�����ɫ����εĲ�һ�������ٽ�������
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
			if (SpriteList.at(i)->getPositionY()>200)
			{
				SpriteList.at(i)->setPositionY(200);
			}
		}
		ChoseSprite_->setPositionY(pt.y - 80);
		if (ChoseSprite_->getPositionY() > 200)
		{
			ChoseSprite_->setPositionY(200);
		}
	}
}
//�����¼�������Ҳ������ָ�ɿ�ʱ  
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
				
				//���㵱ǰ���ĵ� ��������������ĵ���ɫˮ�� ����� ��������ĵ���ɫˮ������
				CBattleUIManager* manager = static_cast<CBattleUIManager*>(this->getParent());
				bool flag = false;
				if (!CGameSceneControl::GetInstance()->IsHaveConsumeHero(LaseChoseColor, ChoseNum))
				{
					flag = true; 
					if (LaseChoseColor == 5)
					{
						manager->UpdateCaiSeShuiJing(5);
					}
					else
					{
						manager->UpdateCaiSeShuiJing(ChoseNum);
					}
				
				}
				int temp = StartIndex > lastIndex ? lastIndex : StartIndex;
				for (int i = 0; i < ChoseNum; i++)
				{
					int rand = random(1, 4);
					SpriteList.at(temp)->ResetInfo(i+1,rand);
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
				UpdateCanChoseShuiJing();
			}
		}
		else
		{
			ChoseSprite_->setScaleX(0);
			for (int i = 0; i < SpriteList.size(); i++)
			{
				SpriteList.at(i)->setPosition(init_x + 170 * i, init_y);
			}
			lastIndex = -1;
		}
	}

}
//��ϴ����¼���һ����ϵͳ�㼶����Ϣ�������绰�������¼��ͻᱻ���  
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

