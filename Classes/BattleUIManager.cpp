#include "BattleUIManager.h"

#include "BattleObjectManager.h"
USING_NS_CC;

bool CBattleUIManager::init()

{
	if (!Node::init())
	{
		return false;
	}
	setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
	DiamondManger = CDiamondChoseManager::create();
	DiamondManger->setAnchorPoint(Vec2(0, 0));
	DiamondManger->setPosition(310, 0);
	addChild(DiamondManger);
	//创建我方阵容头像
	for (int i = 0; i < 6; i++)
	{
		BattleIcon* icon = BattleIcon::create();
		icon->SetInfo(i + 1, i, i / 2);
		icon->setAnchorPoint(Vec2(0, 1));
		icon->setPosition(50 + i % 3 * 70, 220 - (i / 3) * 80);
		addChild(icon);
		IconList.pushBack(icon);
	}
	//创建双方基地的血量显示
	CreateFirstBase();
	CreateSecondBase();

	CreateCaiSeShuiJing();
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
	this->scheduleUpdate();
	return true;
}
//显示彩色水晶的信息
void CBattleUIManager::CreateCaiSeShuiJing()
{

	Sprite*spritebg = Sprite::createWithSpriteFrameName("caisebg.png");
	spritebg->setAnchorPoint(Vec2(1, 0));
	spritebg->setPosition(Vec2(Director::getInstance()->getWinSize().width, 0));
	addChild(spritebg);
	CaiseShuiJingRoot_ = Node::create();
	CaiseShuiJingRoot_->setAnchorPoint(Vec2(1, 0));
	CaiseShuiJingRoot_->setPosition(Vec2(Director::getInstance()->getWinSize().width - 25, 18));
	addChild(CaiseShuiJingRoot_);
	Sprite*spritebg1 = Sprite::createWithSpriteFrameName("caisebg1.png");
	spritebg1->setAnchorPoint(Vec2(1, 0));
	spritebg1->setPosition(0, 0);
	CaiseShuiJingRoot_->addChild(spritebg1);
	auto stencil = Sprite::createWithSpriteFrameName("caiseup2.png");
	stencil->setScale(1);//2
	stencil->setAnchorPoint(Vec2(1, 0));
	auto clipper = ClippingNode::create();
	clipper->setAnchorPoint(Vec2(1, 0));
	clipper->setPosition(0, 0);
	clipper->setStencil(stencil);//设置裁剪模板 //3
	clipper->setInverted(false);//设置底板可见
	clipper->setAlphaThreshold(0);//设置绘制底板的Alpha值为0

	CaiseShuiJingRoot_->addChild(clipper);//4
	Vector<SpriteFrame*> vsp;
	for (int i = 0; i < 24; i++)
	{
		String *string = String::createWithFormat("caihong_%d.png", i);
		SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
		vsp.pushBack(spfr);
	}

	Animation* animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
	Animate* animate = Animate::create(animation);
	auto *ac1 = RepeatForever::create(animate);
	CaiSeShuiJing_ = Sprite::createWithSpriteFrameName("caihong_0.png");//被裁剪的内容
	CaiSeShuiJing_->setAnchorPoint(Vec2(1, 0));
	CaiSeShuiJing_->setScaleY(0);
	CaiSeShuiJing_->runAction(ac1);
	clipper->addChild(CaiSeShuiJing_);//5

	Sprite*spritebg2 = Sprite::createWithSpriteFrameName("caiseup1.png");
	spritebg2->setAnchorPoint(Vec2(1, 0));
	spritebg2->setPosition(0, 0);
	CaiseShuiJingRoot_->addChild(spritebg2);
	TTFConfig config("fonts/ARLRDBD.TTF", 25);
	std::string str = "0%";
	CaiSeShuiJingLabel_ = Label::createWithTTF(config, str, TextHAlignment::LEFT);
	CaiSeShuiJingLabel_->setAnchorPoint(Vec2(1, 0));
	CaiSeShuiJingLabel_->setPosition(Vec2(Director::getInstance()->getWinSize().width - 80, 150));
	CaiSeShuiJingLabel_->setTextColor(Color4B::BLUE);
	addChild(CaiSeShuiJingLabel_);
}
//显示第一队伍的基地信息
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
	TTFConfig config("fonts/ERASDEMI.TTF", 50);
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
	TTFConfig config2("fonts/ARLRDBD.TTF", 40);
	MyBloodDesc_ = Label::createWithTTF(config2, "1000/1000", TextHAlignment::LEFT);
	MyBloodDesc_->setAnchorPoint(Vec2(0.5, 0.5));
	MyBloodDesc_->setTextColor(Color4B::RED);
	MyBloodDesc_->setPosition(300, Director::getInstance()->getWinSize().height - 90);
	
	addChild(MyBloodDesc_);
}
//显示第二队伍的基地信息
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
	TTFConfig config("fonts/ERASDEMI.TTF", 50);
	SecondName_ = Label::createWithTTF(config, "player2", TextHAlignment::LEFT);
	SecondName_->setAnchorPoint(Vec2(0.5, 0.5));
	SecondName_->setTextColor(Color4B::GREEN);
	SecondName_->setPosition(Director::getInstance()->getWinSize().width - 220, Director::getInstance()->getWinSize().height - 25);
	addChild(SecondName_);
	Sprite*progressbg = Sprite::createWithSpriteFrameName("xuetiaobg.png");
	progressbg->setRotationY(-180);
	progressbg->setAnchorPoint(Vec2(0.5, 0.5));
	progressbg->setPosition(Director::getInstance()->getWinSize().width - 300, Director::getInstance()->getWinSize().height - 100);
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
	TTFConfig config2("fonts/ARLRDBD.TTF", 40);
	SecondBloodDesc_ = Label::createWithTTF(config2, "1000/1000", TextHAlignment::LEFT);
	SecondBloodDesc_->setAnchorPoint(Vec2(0.5, 0.5));
	SecondBloodDesc_->setTextColor(Color4B::RED);
	SecondBloodDesc_->setPosition(Director::getInstance()->getWinSize().width - 300, Director::getInstance()->getWinSize().height - 90);
	addChild(SecondBloodDesc_);
}
void CBattleUIManager::update(float delta)
{

	if (CBattleObjectManager::GetInstance()->GetFirstRanksBoss() != nullptr&&MyBloodProgress_ != nullptr&&MyBloodDesc_ != nullptr)
	{
		CBaseBoss* boss = CBattleObjectManager::GetInstance()->GetFirstRanksBoss();
		MyBloodProgress_->setPercentage(boss->CurHp * 100 / boss->MaxHp);

		String* str = String::createWithFormat("%d/%d", boss->CurHp, boss->MaxHp);
		MyBloodDesc_->setString(str->getCString());
	}
	if (CBattleObjectManager::GetInstance()->GetSecondRanksBoss() != nullptr&&SecondBloodDesc_ != nullptr&&SecondBloodProgress_ != nullptr)
	{
		CBaseBoss* boss = CBattleObjectManager::GetInstance()->GetSecondRanksBoss();
		SecondBloodProgress_->setPercentage(boss->CurHp * 100 / boss->MaxHp);
		String* str = String::createWithFormat("%d/%d", boss->CurHp, boss->MaxHp);
		SecondBloodDesc_->setString(str->getCString());
	}
}

void CBattleUIManager::UpdateCaiSeShuiJing(int num)
{
	CurCaiSeShuiJingPrecentNum_ += num;
	float val = CurCaiSeShuiJingPrecentNum_ / 5.0f;
	CCLOG("%.2f", val);
	if (val >= 0.99)
	{
		CaiSeShuiJing_->setScaleY(1.4);
		IsCanChoseCaiSe_ = true;
	}
	else
	{
		CaiSeShuiJing_->setScaleY(val);
		IsCanChoseCaiSe_ = false;
	}

	String* str = String::createWithFormat("%.0f%%", val * 100);
	CaiSeShuiJingLabel_->setString(str->getCString());
}
void CBattleUIManager::CreateMoveAnimation(int color,CCPoint start, CCPoint target)
{
	if (color == 3)
		color = 2;
	if (color == 2)
		color = 3;
	String* str = String::createWithFormat("shujing_%d.png", color);
	Sprite* sprite = Sprite::createWithSpriteFrameName(str->getCString());
	sprite->setTag(100);
	sprite->setPosition(start);
	CCMoveTo* move = CCMoveTo::create(1, target);
	CCFiniteTimeAction* ac = CCSequence::create(move, CallFuncN::create(std::bind(&CBattleUIManager::OnMoveAnimationComplete, this, sprite)) , NULL);
	
	sprite->runAction(ac);
	addChild(sprite);
}
void CBattleUIManager::OnMoveAnimationComplete(cocos2d::CCSprite* spr)
{
	spr->removeFromParent();
}
//触摸事件开始，手指按下时  
void CBattleUIManager::onTouchBegan(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		if (pt.x > nw - 186 && pt.y < 184)
		{
			//点中彩色水晶
			IsChoseCaiSe_ = true;
		}
	}

}
//触摸移动事件，也就是手指在屏幕滑动的过程  
void CBattleUIManager::onTouchMoved(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		if (IsChoseCaiSe_ == true)
		{
			CaiseShuiJingRoot_->setPosition(pt.x + 70, pt.y - 80);
		}
	}

}
//触摸事件结束，也就是手指松开时  
void CBattleUIManager::onTouchEnded(Touch* touch, Event* event)
{
	CCPoint pt = convertTouchToNodeSpace(touch);
	int nw = getContentSize().width;
	int nh = getContentSize().height;
	CCRect rc(0, 0, nw, nh);
	if (rc.containsPoint(pt))
	{
		IsChoseCaiSe_ = false;
		CCPoint pos = touch->getPreviousLocation();
		CaiseShuiJingRoot_->setPosition(getContentSize().width - 25, 18);
		if (IsCanChoseCaiSe_ == true)
		{
			if (DiamondManger->CheckPointInThis(pos))
			{
				UpdateCaiSeShuiJing(-5);
			}
		}
	}

}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断  
void CBattleUIManager::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}
