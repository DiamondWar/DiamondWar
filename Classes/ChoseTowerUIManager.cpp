#include "ChoseTowerUIManager.h"
#include "cocostudio/CocoStudio.h"
#include "HelloWorldScene.h"
#include "GameDataManager.h"
#include "SoliderConfig.h"
#include "SkillConfig.h"
#include "BattleUIManager.h"
#include "GameSceneControl.h"
#include "AttackConfig.h"
#include "StrengthConfig.h"
#include "AudioManager.h"
#include "EnemyLevelConfig.h"
#include "SpellConfig.h"
USING_NS_CC;
Scene* CChoseTowerUIManager::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CChoseTowerUIManager::create();

	// add layer as a child to scene
	scene->addChild(layer);
	return scene;
}
bool CChoseTowerUIManager::init()
{
	if (!Layer::init())
		return false;
	//加载配置文件
	CSoliderConfig::GetInstance()->LoadText();
	CSkillConfig::GetInstance()->LoadText();
	CAttackConfig::GetInstance()->LoadText();
	CStrengthConfig::GetInstance()->LoadText();
	CEnemyLevelConfig::GetInstance()->LoadText();
	CSpellConfig::GetInstance()->LoadText();

	auto*node = CSLoader::createNode("ChoseTowerRoot.csb");
	auto* title1 = node->getChildByName("cost_title_1");
	auto *title2 = node->getChildByName("cost_title_2");
	auto *title3 = node->getChildByName("cost_title_3");
	auto *title4 = node->getChildByName("cost_title_4");
	auto * title5 = node->getChildByName("cost_title_5");
	ScrollView_ = static_cast<ScrollView*>(node->getChildByName("ScrollView_1"));
	ScrollView_->setVisible(false);
	title1->setPosition(Init_x + 60, Init_y + 50);
	title2->setPosition(Init_x + 160 + 60, Init_y + 50);
	title3->setPosition(Init_x + 320 + 60, Init_y + 50);
	title4->setPosition(Init_x + 480 + 60, Init_y + 50);
	title5->setPosition(Init_x + 640 + 60, Init_y + 50);
	StartGame = static_cast<Button*>(node->getChildByName("Button_1"));
	StartGame->setPressedActionEnabled(true);
	StartGame->setEnabled(true);
	StartGame->addClickEventListener(CC_CALLBACK_0(CChoseTowerUIManager::OnStartButtonClickHandleEvent, this));
	addChild(node);
	for (int i = 0; i < 20; i++)
	{
		CTowerItemUI* item = CTowerItemUI::create();
		item->InitInfo(i, 0, false);
		item->SetCanChose(CGameDataManager::GetInstance()->IsHaveHeroByNeedStar(i % 5 + 1, i / 5 + 1));
		item->setPosition(Init_x + i % 5 * 160, Init_y - i / 5 * 160);
		item->ChoseDelegate_ = this;
		addChild(item);
		ShowTowerList_.pushBack(item);
	}
	for (int i = 1; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i != 4)
			{
				Vector<CSoliderData*> list = CGameDataManager::GetInstance()->GetHeroListByNeedStar(j+1, i);
				Vector<CTowerItemUI*> uilist;
				for (int n = 0; n < list.size(); n++)
				{
					
					CTowerItemUI* item = CTowerItemUI::create();
					item->InitInfo(n, list.at(n)->ID, true);
					item->setPosition(n*150,ScrollView_->getContentSize().height);
					ScrollView_->addChild(item);
					item->setVisible(false);
					uilist.pushBack(item);

				}
				CanChoseItemList_[(i-1)*5+j] = uilist;
			}
			else
			{
				Vector<CSpellData*> list = CGameDataManager::GetInstance()->GetSpellListByNeedStar(j);
				Vector<CTowerItemUI*> uilist;
				for (int n = 0; n < list.size(); n++)
				{

					CTowerItemUI* item = CTowerItemUI::create();
					item->InitInfo(n, list.at(n)->ID, true);
					item->setPosition(n*150, ScrollView_->getContentSize().height);
					ScrollView_->addChild(item);
					item->setVisible(false);
					uilist.pushBack(item);

				}
				CanChoseItemList_[(i - 1) * 5 + j] = uilist;
			}
		}


	}
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
		onTouchEnded(touch, event);
	};
	listener->onTouchCancelled = [this](Touch* touch, Event* event)
	{
		onTouchCancelled(touch, event);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}
void CChoseTowerUIManager::OnStartButtonClickHandleEvent()
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}
void CChoseTowerUIManager::OnChoseTowerShowList(int index)
{
	Vector<CTowerItemUI*>list = CanChoseItemList_[CurChoseIndex_];
	for (int i = 0; i < list.size(); i++)
	{
		list.at(i)->setVisible(false);
	}
	Vector<CTowerItemUI*>list1 = CanChoseItemList_[index];
	for (int i = 0; i < list1.size(); i++)
	{
		list1.at(i)->setVisible(true);
	}
}
void CChoseTowerUIManager::OnChoseTower(int index, bool flag)
{
	for (int i = 0; i < ShowTowerList_.size(); i++)
	{
		ShowTowerList_.at(i)->SetIsChose(i == index);
	}
	OnChoseTowerShowList(index);
	CurChoseIndex_ = index;
}
void CChoseTowerUIManager::ClickTower(int index)
{

}
//触摸事件开始，手指按下时  
bool CChoseTowerUIManager::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}
//触摸移动事件，也就是手指在屏幕滑动的过程  
void CChoseTowerUIManager::onTouchMoved(Touch* touch, Event* event)
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
void CChoseTowerUIManager::onTouchEnded(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(Init_x, 140, 850, 700);
	CCRect rc1(ScrollView_->getPositionX(), ScrollView_->getPositionY() - ScrollView_->getContentSize().height, ScrollView_->getContentSize().width, ScrollView_->getContentSize().height);
	if (rc.containsPoint(pt))
	{
		CCLOG("rc.containsPoint(pt)");
		int star = (pt.x - Init_x) / 160;
		int type = (Init_y - pt.y) / 170;
		int index = star + type * 5;
		for (int i = 0; i < ShowTowerList_.size(); i++)
		{
			ShowTowerList_.at(i)->SetIsChose(i == (index));
		}
		OnChoseTowerShowList(index);
		CurChoseIndex_ = index;
	}
	else if (rc1.containsPoint(pt))
	{
		CCLOG("rc1.containsPoint(pt)");
	}

}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断  
void CChoseTowerUIManager::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}