#include "BattleUIManager.h"
#include "cocostudio/CocoStudio.h"
#include "BattleObjectManager.h"
#include "GameSceneControl.h"
#include "SoliderConfig.h"
USING_NS_CC;

bool CBattleUIManager::init()

{
	if (!Node::init())
	{
		return false;
	}
	auto *node = CSLoader::createNode("MainScene.csb");
	MyBloodProgress_ =static_cast<LoadingBar*>( node->getChildByName("LoadingBar_1"));
	SecondBloodProgress_ = static_cast<LoadingBar*>(node->getChildByName("LoadingBar_2"));
	addChild(node);
 	setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
	DiamondManger = CDiamondChoseManager::create();
	DiamondManger->setAnchorPoint(Vec2(0, 0));
	DiamondManger->setPosition(310, 0);
	addChild(DiamondManger);
	CreateTime();
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
	/*CCSprite*spr = CCSprite::createWithSpriteFrameName("Di_%.png");
	spr->setPosition(Vec2(Director::getInstance()->getWinSize().width - 80-30, 150));
	addChild(spr);*/
	CaiSeShuiJingTimeLabel_ = TextAtlas::create("12780", "diatlas.png", 45, 37, "/");
	CaiSeShuiJingTimeLabel_->setString("12/");
	CaiSeShuiJingTimeLabel_->setPosition(Vec2(Director::getInstance()->getWinSize().width - 80, 150));
	addChild(CaiSeShuiJingTimeLabel_);
}
void CBattleUIManager::CreateTime()
{
	for (int i = 0; i < 5;i++)
	{
		if (i != 2)
		{
			Sprite*sprite = Sprite::createWithSpriteFrameName("Ding_0.png");
			sprite->setPosition(900 + i * 40, 1000);
			addChild(sprite);
			TimeList_.pushBack(sprite);
		}
		else
		{
			Sprite*sprite = Sprite::createWithSpriteFrameName("Ding_Q.png");
			sprite->setPosition(902 + i * 40, 1000);
			addChild(sprite);
			TimeList_.pushBack(sprite);
		}
	}
}

void CBattleUIManager::ShowTime()
{
	int last =(int) (MaxTime - DetiaTime);
	if (last < 0)
	{
		last = 0;
		DiamondManger->SetCanShengChengShuiJing();
		return;
	}
		
	int se = last / 60;
	int miao = last % 60; 
	String*str = String::createWithFormat("Ding_%d.png", se / 10);
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str->getCString());
	TimeList_.at(0)->setSpriteFrame(frame);
	String*str1 = String::createWithFormat("Ding_%d.png", se% 10);
	SpriteFrame* frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str1->getCString());
	TimeList_.at(1)->setSpriteFrame(frame1);
	String*str2= String::createWithFormat("Ding_%d.png", miao / 10);
	SpriteFrame* frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(str2->getCString());
	TimeList_.at(3)->setSpriteFrame(frame2);
	String*str3= String::createWithFormat("Ding_%d.png", miao% 10);
	SpriteFrame* frame3= SpriteFrameCache::getInstance()->getSpriteFrameByName(str3->getCString());
	TimeList_.at(4)->setSpriteFrame(frame3);
}
void CBattleUIManager::update(float delta)
{
	DetiaTime += delta;
	ShowTime();
	if (CBattleObjectManager::GetInstance()->GetFirstRanksBoss() != nullptr&&MyBloodProgress_ != nullptr)
	{
		CBaseBoss* boss = CBattleObjectManager::GetInstance()->GetFirstRanksBoss();
		MyBloodProgress_->setPercent(boss->CurBlood * 100 / boss->MaxBlood);

	}
	if (CBattleObjectManager::GetInstance()->GetSecondRanksBoss() != nullptr&&SecondBloodProgress_ != nullptr)
	{
		CBaseBoss* boss = CBattleObjectManager::GetInstance()->GetSecondRanksBoss();
		SecondBloodProgress_->setPercent(boss->CurBlood * 100 / boss->MaxBlood);
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
	String*string = String::createWithFormat("%.0f", val * 100);
	CaiSeShuiJingTimeLabel_->setString(string->getCString());

}
void CBattleUIManager::CreateMoveAnimation(int color, CCPoint start, CCPoint target)
{
	String* str = String::createWithFormat("shuijing_%d.png", color);
	Sprite* sprite = Sprite::createWithSpriteFrameName(str->getCString());
	sprite->setTag(100);
	sprite->setPosition(start);
	CCMoveTo* move = CCMoveTo::create(1, target);
	CCFiniteTimeAction* ac = CCSequence::create(move, CallFuncN::create(std::bind(&CBattleUIManager::OnMoveAnimationComplete, this, sprite)), NULL);

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
			IsMoveChoseCaiSe_ = false;
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
			IsMoveChoseCaiSe_ = true;
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
		if (IsMoveChoseCaiSe_ == true)
		{
			IsMoveChoseCaiSe_ = false;
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

}
//打断触摸事件，一般是系统层级的消息，如来电话，触摸事件就会被打断  
void CBattleUIManager::onTouchCancelled(Touch* touch, Event* event)
{
	log("TouchTest onTouchesCancelled");
}
