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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ChoseTower.plist", "ChoseTower.png");
	//加载配置文件
	CSoliderConfig::GetInstance()->LoadText();
	CSkillConfig::GetInstance()->LoadText();
	CAttackConfig::GetInstance()->LoadText();
	CStrengthConfig::GetInstance()->LoadText();
	CEnemyLevelConfig::GetInstance()->LoadText();
	CSpellConfig::GetInstance()->LoadText();
	//加载音乐
	CAudioManager::GetInstance()->PreLoadAudioBackground("Audio/audio_chosebg.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_startgame.mp3");
	CAudioManager::GetInstance()->PreLoadAudio("Audio/audio_chosehero.mp3");
	auto*node = CSLoader::createNode("ChoseTowerRoot.csb");
	auto* title1 = node->getChildByName("cost_title_1");
	auto *title2 = node->getChildByName("cost_title_2");
	auto *title3 = node->getChildByName("cost_title_3");
	auto *title4 = node->getChildByName("cost_title_4");
	auto * title5 = node->getChildByName("cost_title_5");
	XinShouSp1 = Sprite::createWithSpriteFrameName("xinshouyindao_1.png");
	XinShouSp1->setAnchorPoint(ccp(1, 0));
	XinShouSp1->setPosition(1700, 0);
	XinshouSp2 = Sprite::createWithSpriteFrameName("xinshouyindao_2.png");
	XinshouSp2->setAnchorPoint(ccp(1, 0));
	XinshouSp2->setPosition(1700, 0);
	XinShouSp3 = Sprite::createWithSpriteFrameName("xinshouyindao_3.png");
	XinShouSp3->setAnchorPoint(ccp(1, 0));
	XinShouSp3->setPosition(1700, 0);
	XinShouSp4 = Sprite::createWithSpriteFrameName("xinshouyindao_ren.png");
	XinShouSp4->setAnchorPoint(ccp(1, 0));
	XinShouSp4->setPosition(1920, 0);
	XinShouSp5 = node->getChildByName("xinshouyindao_6");
	XinShouButton_ = static_cast<Button*>(node->getChildByName("Button_2"));
	XinShouButton_->addClickEventListener(CC_CALLBACK_0(CChoseTowerUIManager::OnXinShouButtonClickHandleEvent, this));
	XinShouSp6 = Node::create();
	Sprite*sp1 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp1->setAnchorPoint(ccp(0, 1));
	sp1->setPosition(Init_x + 2 * 160 - 20, Init_y + 20);
	XinShouSp6->addChild(sp1);
	Sprite*sp2 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp2->setAnchorPoint(ccp(0, 1));
	sp2->setPosition(Init_x + 4 * 160 - 20, Init_y + 20);
	XinShouSp6->addChild(sp2);
	Sprite*sp3 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp3->setAnchorPoint(ccp(0, 1));
	sp3->setPosition(Init_x - 20, Init_y - 160 + 20);
	XinShouSp6->addChild(sp3);
	Sprite*sp4 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp4->setAnchorPoint(ccp(0, 1));
	sp4->setPosition(Init_x + 2 * 160 - 20, Init_y - 160 + 20);
	XinShouSp6->addChild(sp4);
	Sprite*sp5 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp5->setAnchorPoint(ccp(0, 1));
	sp5->setPosition(Init_x + 160 - 20, Init_y - 320 + 20);
	XinShouSp6->addChild(sp5);
	Sprite*sp6 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp6->setAnchorPoint(ccp(0, 1));
	sp6->setPosition(Init_x + 3 * 160 - 20, Init_y - 320 + 20);
	XinShouSp6->addChild(sp6);
	Sprite*sp7 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp7->setAnchorPoint(ccp(0, 1));
	sp7->setPosition(Init_x + 160 - 20, Init_y - 480 + 20);
	XinShouSp6->addChild(sp7);
	Sprite*sp8 = Sprite::createWithSpriteFrameName("xinshouyindao_kuang.png");
	sp8->setAnchorPoint(ccp(0, 1));
	sp8->setPosition(Init_x + 4 * 160 - 20, Init_y - 480 + 20);
	XinShouSp6->addChild(sp8);
	XinShouSp6->setAnchorPoint(ccp(0, 0));
	XinShouSp6->setPosition(0, 0);

	ScrollView_ = static_cast<ScrollView*>(node->getChildByName("ScrollView_1"));
	ChoseTitleSp_ = static_cast<Sprite*>(node->getChildByName("chosetitlebg"));
	ChoseTilteText_ = static_cast<TextAtlas*>(node->getChildByName("chosestar"));
	ScrollView_->setVisible(false);
	title1->setPosition(Init_x + 60, Init_y + 50);
	title2->setPosition(Init_x + 160 + 60, Init_y + 50);
	title3->setPosition(Init_x + 320 + 60, Init_y + 50);
	title4->setPosition(Init_x + 480 + 60, Init_y + 50);
	title5->setPosition(Init_x + 640 + 60, Init_y + 50);
	StartGame = static_cast<Button*>(node->getChildByName("Button_1"));
	StartGame->setPressedActionEnabled(true);
	StartGame->setEnabled(false);
	StartGame->addClickEventListener(CC_CALLBACK_0(CChoseTowerUIManager::OnStartButtonClickHandleEvent, this));
	addChild(node);
	TypeList[0] = 0;
	TypeList[1] = 0;
	TypeList[2] = 0;
	TypeList[3] = 0;
	for (int i = 0; i < 20; i++)
	{
		CTowerItemUI* item = CTowerItemUI::create();
		item->InitInfo(i, 0, false);
		item->SetCanChose(CGameDataManager::GetInstance()->IsHaveHeroByNeedStar(i % 5 + 1, i / 5 + 1));
		item->setPosition(Init_x + i % 5 * 160, Init_y - i / 5 * 160);
		CCLOG("%f , %f", item->getPositionX(), item->getPositionY());
		item->ChoseDelegate_ = this;
		addChild(item);
		ShowTowerList_.pushBack(item);
	}
	addChild(XinShouSp6);
	
	for (int n = 0; n < 12; n++)
	{
		Sprite*sprite = Sprite::createWithSpriteFrameName("choseTower_iconbg.png");
		sprite->setAnchorPoint(ccp(0, 1));
		sprite->setPosition(ScrollView_->getPositionX() + 25 + n % 3 * 170, ScrollView_->getPositionY() - n / 3 * 150);
		addChild(sprite);
	}
	addChild(XinShouSp4);
	addChild(XinShouSp1);
	addChild(XinshouSp2);
	addChild(XinShouSp3);
	for (int i = 1; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i != 4)
			{
				Vector<CSoliderData*> list = CGameDataManager::GetInstance()->GetHeroListByNeedStar(j + 1, i);
				Vector<CTowerItemUI*> uilist;
				for (int n = 0; n < list.size(); n++)
				{

					CTowerItemUI* item = CTowerItemUI::create();
					item->InitInfo(n, list.at(n)->ID, true);
					item->setPosition(ScrollView_->getPositionX() + 25 + n % 3 * 170, ScrollView_->getPositionY() - n / 3 * 150);
					addChild(item);
					item->setVisible(false);
					uilist.pushBack(item);

				}
				CanChoseItemList_[(i - 1) * 5 + j] = uilist;
			}
			else
			{
				Vector<CSpellData*> list = CGameDataManager::GetInstance()->GetSpellListByNeedStar(j + 1);
				Vector<CTowerItemUI*> uilist;
				for (int n = 0; n < list.size(); n++)
				{

					CTowerItemUI* item = CTowerItemUI::create();
					item->InitInfo(n, list.at(n)->ID, true);
					item->setPosition(ScrollView_->getPositionX() + 25 + n % 3 * 170, ScrollView_->getPositionY() - n / 3 * 150);
					addChild(item);
					item->setVisible(false);
					uilist.pushBack(item);

				}
				CanChoseItemList_[(i - 1) * 5 + j] = uilist;
			}
		}


	}
	CAudioManager::GetInstance()->PlayerBackGroundMusic("audio_chosebg");
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
	OnXinShouButtonClickHandleEvent();
	return true;
}
void CChoseTowerUIManager::OnXinShouButtonClickHandleEvent()
{
	xinshouNum++;
	switch (xinshouNum)
	{
	case 1:
		XinShouSp1->setVisible(true);
		XinshouSp2->setVisible(false);
		XinShouSp3->setVisible(false);
		XinShouSp6->setVisible(false);
		break;
	case 2:
		XinShouSp1->setVisible(false);
		XinshouSp2->setVisible(true);
		XinShouSp3->setVisible(false);
		XinShouSp6->setVisible(false);
		break;
	case 3:
		XinShouSp1->setVisible(false);
		XinshouSp2->setVisible(false);
		XinShouSp3->setVisible(true);
		XinShouSp6->setVisible(true);
		XinShouSp5->setVisible(false);
		break;
	case 4:
		XinShouSp1->setVisible(false);
		XinshouSp2->setVisible(false);
		XinShouSp3->setVisible(false);
		XinShouSp4->setVisible(false);
		XinShouSp6->setVisible(false);
		XinShouSp5->setVisible(false);
		XinShouButton_->setVisible(false);
		break;
	default:
		break;
	}
}
void CChoseTowerUIManager::OnStartButtonClickHandleEvent()
{
	CAudioManager::GetInstance()->PlayerVoice("audio_startgame");
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
	String* str = String::createWithFormat("%d", index % 5 + 1);
	ChoseTilteText_->setString(str->getCString());
	String* str1 = String::createWithFormat("herotypebg%d.png", index / 5 + 1);
	SpriteFrame * frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1->getCString());
	ChoseTitleSp_->setSpriteFrame(frame);
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
		int star = (pt.x - Init_x) / 160;
		int type = (Init_y - pt.y) / 170;
		int index = star + type * 5;
		if (star >= 5 || type >= 4 || index > 20)
			return;
		for (int i = 0; i < ShowTowerList_.size(); i++)
		{
			ShowTowerList_.at(i)->SetIsChose(i == (index));
		}
		OnChoseTowerShowList(index);
		CurChoseIndex_ = index;
	}
	else if (rc1.containsPoint(pt))
	{
		int star = (pt.x - ScrollView_->getPositionX()) / 170;
		int type = (ScrollView_->getContentSize().height - pt.y) / 150;
		int index = star + type * 5;
		if (index > CanChoseItemList_[CurChoseIndex_].size() - 1 || index < 0)
		{
			return;
		}
		if (CanChoseItemList_[CurChoseIndex_].at(index)->IsChosing_)
		{
			CanChoseItemList_[CurChoseIndex_].at(index)->SetIsChose(false);
			ShowTowerList_.at(CurChoseIndex_)->SetInfo(0);
			TypeList[CurChoseIndex_ / 5]--;
			StartGame->setEnabled(false);
		}
		else
		{
			if (TypeList[CurChoseIndex_ / 5] == 2)
			{
				return;
			}
			for (int i = 0; i < CanChoseItemList_[CurChoseIndex_].size(); i++)
			{
				CanChoseItemList_[CurChoseIndex_].at(i)->SetIsChose(i == index);
			}
			ShowTowerList_.at(CurChoseIndex_)->SetInfo(CanChoseItemList_[CurChoseIndex_].at(index)->IconId);
			TypeList[CurChoseIndex_ / 5]++;
			CAudioManager::GetInstance()->PlayerVoice("audio_chosehero");
			bool flag = true;
			for (int i = 0; i < 4; i++)
			{
				if (TypeList[i] != 2)
					flag = false;
			}
			if (flag == true)
				StartGame->setEnabled(true);
		}

	}

}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断  
void CChoseTowerUIManager::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}

void CChoseTowerUIManager::onExit()
{
	Layer::onExit();
	
}