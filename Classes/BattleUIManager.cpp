#include "BattleUIManager.h"
#include "DiamondChoseManager.h"
#include "BattleObjectManager.h"
USING_NS_CC;

bool CBattleUIManager::init()

{
	if (!Node::init())
	{
		return false;
	}
	auto manager = CDiamondChoseManager::create();
	manager->setAnchorPoint(Vec2(0, 0));
	manager->setPosition(310, 0);
	addChild(manager);
	//创建我方阵容头像
	for (int i = 0; i < 6; i++)
	{
		BattleIcon* icon = BattleIcon::create();
		icon->SetInfo(i + 1, i, i / 2);
		icon->setAnchorPoint(Vec2(0, 1));
		icon->setPosition(50 + i % 3 * 70, 220 - (i / 3 )* 80);
		addChild(icon);
		IconList.pushBack(icon);
	}
	//创建双方基地的血量显示
	CreateFirstBase();
	CreateSecondBase();
	return true;
}
void CBattleUIManager::CreateFirstBase()
{
	Sprite*bg = Sprite::createWithSpriteFrameName("iconbg.png");
	bg->setAnchorPoint(Vec2(0, 1));
	bg->setPosition(0, Director::getInstance()->getWinSize().height);
	addChild(bg);
	MyIcon_ = Sprite::createWithSpriteFrameName("player1.png");
	MyIcon_->setAnchorPoint(Vec2(0, 1));
	MyIcon_->setPosition(0, Director::getInstance()->getWinSize().height);
	addChild(MyIcon_);
	TTFConfig config("ERASDEMI.ttf", 50);
	MyName_ = Label::createWithTTF(config, "player1", TextHAlignment::LEFT);
	MyName_->setAnchorPoint(Vec2(0.5, 0.5));
	MyName_->setTextColor(Color4B::GREEN);
	MyName_->setPosition(220, Director::getInstance()->getWinSize().height - 25);
	addChild(MyName_);
	Sprite*progressbg = Sprite::createWithSpriteFrameName("xuetiaobg.png");
	progressbg->setAnchorPoint(Vec2(0, 0.5));
	progressbg->setPosition(135, Director::getInstance()->getWinSize().height - 100);
	addChild(progressbg);
	Sprite*progress = Sprite::createWithSpriteFrameName("xuetiaoup.png");
	MyBloodProgress_ = CCProgressTimer::create(progress);
	MyBloodProgress_->setAnchorPoint(Vec2(0, 0.5));
	MyBloodProgress_->setPosition(135, Director::getInstance()->getWinSize().height - 100);
	MyBloodProgress_->setType(kCCProgressTimerTypeBar);
	MyBloodProgress_->setPercentage(100);
	MyBloodProgress_->setMidpoint(Vec2(0, 0));
	MyBloodProgress_->setBarChangeRate(Vec2(1, 0));
	MyBloodProgress_->setPercentage(10);
	addChild(MyBloodProgress_);
	TTFConfig config2("ARLRDBD.TTF", 40);
	MyBloodDesc_ = Label::createWithTTF(config2, "1000/1000", TextHAlignment::LEFT);
	MyBloodDesc_->setAnchorPoint(Vec2(0.5, 0.5));
	MyBloodDesc_->setTextColor(Color4B::RED);
	MyBloodDesc_->setPosition(300, Director::getInstance()->getWinSize().height - 90);
	this->scheduleUpdate();
	addChild(MyBloodDesc_);
}
void CBattleUIManager::CreateSecondBase()
{
	//创建双方基地的血条

	Sprite*bg = Sprite::createWithSpriteFrameName("iconbg.png");
	bg->setAnchorPoint(Vec2(1, 1));
	bg->setPosition(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
	addChild(bg);
	SecondIcon_ = Sprite::createWithSpriteFrameName("player2.png");
	SecondIcon_->setAnchorPoint(Vec2(1, 1));
	SecondIcon_->setPosition(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
	addChild(SecondIcon_);
	TTFConfig config("ERASDEMI.ttf", 50);
	SecondName_ = Label::createWithTTF(config, "player2", TextHAlignment::LEFT);
	SecondName_->setAnchorPoint(Vec2(0.5, 0.5));
	SecondName_->setTextColor(Color4B::GREEN);
	SecondName_->setPosition(Director::getInstance()->getWinSize().width - 220, Director::getInstance()->getWinSize().height - 25);
	addChild(SecondName_);
	Sprite*progressbg = Sprite::createWithSpriteFrameName("xuetiaobg.png");
	progressbg->setRotationY(-180);
	progressbg->setAnchorPoint(Vec2(0.5, 0.5));
	progressbg->setPosition(Director::getInstance()->getWinSize().width - 300,Director::getInstance()->getWinSize().height - 100);
	addChild(progressbg);
	Sprite*progress = Sprite::createWithSpriteFrameName("xuetiaoup.png");
	SecondBloodProgress_ = CCProgressTimer::create(progress);
	
	SecondBloodProgress_->setAnchorPoint(Vec2(0.5, 0.5));
	SecondBloodProgress_->setRotationY(-180);
	SecondBloodProgress_->setPosition(Director::getInstance()->getWinSize().width - 300, Director::getInstance()->getWinSize().height - 100);
	SecondBloodProgress_->setType(kCCProgressTimerTypeBar);
	SecondBloodProgress_->setPercentage(100);
	SecondBloodProgress_->setMidpoint(Vec2(0, 0));
	SecondBloodProgress_->setBarChangeRate(Vec2(1, 0));
	SecondBloodProgress_->setPercentage(75);
	addChild(SecondBloodProgress_);
	TTFConfig config2("ARLRDBD.TTF", 40);
	SecondBloodDesc_ = Label::createWithTTF(config2, "1000/1000", TextHAlignment::LEFT);
	SecondBloodDesc_->setAnchorPoint(Vec2(0.5, 0.5));
	SecondBloodDesc_->setTextColor(Color4B::RED);
	SecondBloodDesc_->setPosition(Director::getInstance()->getWinSize().width - 300, Director::getInstance()->getWinSize().height - 90);
	addChild(SecondBloodDesc_);
}
void CBattleUIManager::update(float delta)
{

	if (CBattleObjectManager::GetInstance()->GetFirstRanksBoss() != nullptr&&MyBloodProgress_!=nullptr&&MyBloodDesc_!=nullptr)
	{
		CBaseBoss* boss = CBattleObjectManager::GetInstance()->GetFirstRanksBoss();
		MyBloodProgress_->setPercentage(boss->CurHp * 100 / boss->MaxHp);
		String*str = String::createWithFormat("%d/%d", boss->CurHp, boss->MaxHp);
		 MyBloodDesc_->setString(str->getCString());
	}
	if (CBattleObjectManager::GetInstance()->GetSecondRanksBoss() != nullptr&&SecondBloodDesc_!=nullptr&&SecondBloodProgress_!=nullptr)
	{
		CBaseBoss* boss = CBattleObjectManager::GetInstance()->GetSecondRanksBoss();
		SecondBloodProgress_->setPercentage(boss->CurHp * 100 / boss->MaxHp);
		String*str = String::createWithFormat("%d/%d", boss->CurHp, boss->MaxHp);
		SecondBloodDesc_->setString(str->getCString());
	}
}
