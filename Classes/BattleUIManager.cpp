#include "BattleUIManager.h"
#include "cocostudio/CocoStudio.h"
#include "BattleObjectManager.h"
#include "GameSceneControl.h"
#include "SoliderConfig.h"
#include "DuiHuaUIManager.h"
#include "ChoseTowerUIManager.h"
#include "AudioManager.h"
#include "SpellConfig.h"
USING_NS_CC;


bool CBattleUIManager::init()

{
	if (!Node::init())
	{
		return false;
	}
	auto *node = CSLoader::createNode("BattleUI.csb");
	MyIcon_ = static_cast<Sprite*>(node->getChildByName("player1_1"));
	MyDuiHuaSp_ = Sprite::createWithSpriteFrameName("texture_nv_start.png");
	MyDuiHuaSp_->setAnchorPoint(ccp(0, 0));
	Sprite*bg1 = Sprite::createWithSpriteFrameName("texture_nv_bg.png");
	bg1->setAnchorPoint(ccp(0, 0));
	bg1->setPosition(180, 940);
	bg1->addChild(MyDuiHuaSp_);
	bg1->setVisible(false);
	addChild(bg1);
	SecondDuiHuaSp_ = Sprite::createWithSpriteFrameName("texture_nan_welcome.png");
	SecondDuiHuaSp_->setAnchorPoint(ccp(0, 0));
	Sprite*bg2 = Sprite::createWithSpriteFrameName("texture_nan_bg.png");
	bg2->setAnchorPoint(ccp(0, 0));
	bg2->addChild(SecondDuiHuaSp_);
	bg2->setPosition(1300, 940);
	bg2->setVisible(false);
	addChild(bg2);
	SecondIcon_ = static_cast<Sprite*>(node->getChildByName("player1_2"));
	MyBloodProgress_ =static_cast<LoadingBar*>( node->getChildByName("LoadingBar_1"));
	SecondBloodProgress_ = static_cast<LoadingBar*>(node->getChildByName("LoadingBar_2"));
	CloseButton_ = static_cast<Button*>(node->getChildByName("Button_1"));
	CloseButton_->setPressedActionEnabled(false);
	CloseButton_->addClickEventListener(CC_CALLBACK_0(CBattleUIManager::OnCloseButtonClicked, this));
	CloseButton_->setScale(0);
	CloseButton_->setVisible(true);
	WinSp_ = static_cast<Sprite*>(node->getChildByName("win_2"));
	WinSp_->setVisible(false);
	FailSp_ = static_cast<Sprite*>(node->getChildByName("fail_1"));
	FailSp_->setVisible(false);
	addChild(node);
 	setContentSize(Size(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
	DiamondManger = CDiamondChoseManager::create();
	DiamondManger->setAnchorPoint(Vec2(0, 0));
	DiamondManger->setPosition(310, 0);
	addChild(DiamondManger);
	CreateTime();
	CreateCaiSeShuiJing();
	OnPlayVoice(3, 2.5);
	CGameSceneControl::GetInstance()->SetBattleUIManager(this);

	FingerAciton_ = Sprite::createWithSpriteFrameName("finger1.png");
	addChild(FingerAciton_);
	
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
	FingerStartTime_ = CCGlobleConfig::GetCurrntTime();
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
	CaiSeShuiJingTimeLabel_ = TextAtlas::create("12780", "diatlas.png", 32, 37, "/");
	CaiSeShuiJingTimeLabel_->setString("0/");
	CaiSeShuiJingTimeLabel_->setPosition(Vec2(Director::getInstance()->getWinSize().width - 90, 100));
	addChild(CaiSeShuiJingTimeLabel_);
}
//给手指确定位置
void CBattleUIManager::CheckToFingerPos()
{
	int num = 0;
	int cutindex = 0;
	for (int i = 0; i < 4; i++)
	{
		int index = CGameSceneControl::GetInstance()->IsHaveHero(DiamondManger->CanChoselist[i]->Color, DiamondManger->CanChoselist[i]->Num);
		if (DiamondManger->CanChoselist[i]->Num>num&&index!=-1)
		{
			if (index < 6)
			{
				CSoliderData* data = CSoliderConfig::GetInstance()->GetItemById(CGameSceneControl::GetInstance()->HeroList[index]);
				num = data->NeedStar;
			}
			else
			{
				CSpellData* data = CSpellConfig::GetInstance()->GetItemById(CGameSceneControl::GetInstance()->HeroList[index]);
				num = data->NeedStar_;
			}
			cutindex = DiamondManger->CanChoselist[i]->indexlist[0];
		}
	}
	StartFingerAnimation(num, DiamondManger->getPositionX() + 120 + 150 * cutindex, DiamondManger->getPositionX() + 120 + 150 * (cutindex + num-1));
}
void CBattleUIManager::OnFingerAnimateComplete()
{
	FingerAciton_->setVisible(false);
}
void CBattleUIManager::StartFingerAnimation(int num, float init_x, float target_x)
{
	FingerAciton_->setVisible(true);
	FingerAciton_->setAnchorPoint(ccp(0, 0));
	FingerAciton_->setPosition(init_x, 85);

	MoveTo* move = MoveTo::create(1, Vec2(target_x, 85));
	Vector<SpriteFrame*> vsp;
	for (int i = 1; i < 11; i++)
	{
		String *string = String::createWithFormat("finger%d.png", i);
		SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
		vsp.pushBack(spfr);
	}
	Animation* animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
	Animate* animate = Animate::create(animation);
	CCCallFunc * funcall = CCCallFunc::create(this, callfunc_selector(CBattleUIManager::OnFingerAnimateComplete));
	if (num > 1)
	{
		CCSequence* sq = CCSequence::create(move, animate, funcall, NULL);
		FingerAciton_->runAction(sq);
	}
	else
	{
		CCSequence* sq = CCSequence::create(animate, funcall, NULL);
		FingerAciton_->runAction(sq);
	}
	
	
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
	if (IsEndGame_ == true)
		return;
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

	if (CCGlobleConfig::GetCurrntTime() > FingerStartTime_ + ContinueTime)
	{
		FingerStartTime_ = CCGlobleConfig::GetCurrntTime();
		CheckToFingerPos();
	}
	if (CCGlobleConfig::IsEndGame_ == true)
	{
		IsEndGame_ = true;
		OnEndGameAnimation();
	}
}
void CBattleUIManager::OnCloseButtonClicked()
{
	Director::getInstance()->replaceScene(CChoseTowerUIManager::createScene());
}
void CBattleUIManager::OnEndGameAnimation()
{
	ScaleTo* scale = ScaleTo::create(1, 1);
	if (CCGlobleConfig::IsWinGame_ == true)
	{
		WinSp_->setVisible(true);
		WinSp_->setScale(0);
		WinSp_->runAction(scale);
	}
	else
	{
		FailSp_->setVisible(true);
		FailSp_->setScale(0);
		FailSp_->runAction(scale);
	}
	
	CloseButton_->setVisible(true);
	CloseButton_->setScale(1);

	if (CCGlobleConfig::IsWinGame_ == true)
		CAudioManager::GetInstance()->PlayerVoice("audio_win");
	else
		CAudioManager::GetInstance()->PlayerVoice("audio_fail");
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
	String*string = String::createWithFormat("%.0f/", val * 100);
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
					//播放声音
					OnPlayVoice(5,2);
					FingerStartTime_ = CCGlobleConfig::GetCurrntTime();
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

void CBattleUIManager::Role1PlayAnimation(int index)
{
	String *string = String::createWithFormat("nv_animation_%d", index);
	Animation* animation = AnimationCache::getInstance()->getAnimation(string->getCString());
	if (animation==NULL)
	{
		Vector<SpriteFrame*> vsp;
		for (int i = 1; i < 3; i++)
		{
			String *string1 = String::createWithFormat("texture_nv_%d_%d.png", index, i);
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string1->getCString());
			vsp.pushBack(spfr);
		}
		animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);
		
		AnimationCache::getInstance()->addAnimation(animation, string->getCString());
	}
	
	Animate* animate = Animate::create(animation);
	auto *ac1 = RepeatForever::create(animate);
	MyIcon_->runAction(ac1);
}
void CBattleUIManager::Role2PlayAnimation(int index)
{
	String *string = String::createWithFormat("nan_animation_%d", index);
	Animation* animation = AnimationCache::getInstance()->getAnimation(string->getCString());
	if (animation == NULL)
	{
		Vector<SpriteFrame*> vsp;
		for (int i = 1; i < 3; i++)
		{
			String *string1 = String::createWithFormat("texture_nan_%d_%d.png", index, i);
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string1->getCString());
			vsp.pushBack(spfr);
		}
		animation = Animation::createWithSpriteFrames(vsp, 1.0f / 10);

		AnimationCache::getInstance()->addAnimation(animation, string->getCString());
	}

	Animate* animate = Animate::create(animation);
	auto *ac1 = RepeatForever::create(animate);

	if (SecondIcon_!= NULL)
	SecondIcon_->runAction(ac1);
}
void CBattleUIManager::OnPlayVoice(int index,float time)
{
	SpriteFrame* frame1;
	switch (index)
	{
	case 1:
		Role2PlayAnimation(2);
		SecondDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nan_golden.png");
		SecondDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 2:
		Role2PlayAnimation(1);
		SecondDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nan_haha.png");
		SecondDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 3:
		Role2PlayAnimation(1);
		SecondDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nan_welcome.png");
		SecondDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 4:
		Role2PlayAnimation(1);
		SecondDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nan_welldone.png");
		SecondDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 5:
		Role1PlayAnimation(1);
		MyDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nv_caiseshuijing.png");
		MyDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 6:
		Role1PlayAnimation(1);
		MyDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nv_choice.png");
		MyDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case  7:
		Role1PlayAnimation(2);
		MyDuiHuaSp_->getParent()->setVisible(true);
		frame1 =  SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nv_heropower.png");
		MyDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 8:
		Role1PlayAnimation(1);
		MyDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nv_hewin.png");
		MyDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 9:
		Role1PlayAnimation(2);
		MyDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nv_monkey.png");
		MyDuiHuaSp_->setSpriteFrame(frame1);
		break;
	case 10:
		Role1PlayAnimation(1);
		MyDuiHuaSp_->getParent()->setVisible(true);
		frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("texture_nv_start.png");
		MyDuiHuaSp_->setSpriteFrame(frame1);
		break;
	default:
		break;
	}
	CDuiHuaUIManager* duihua = CDuiHuaUIManager::create();
	duihua->PlayPersonAudio(index, time, this);
	addChild(duihua);
}
void CBattleUIManager::OnAudioComplete(int index)
{
	MyIcon_->stopAllActions();
	SecondIcon_->stopAllActions();
	SecondDuiHuaSp_->getParent()->setVisible(false);
	MyDuiHuaSp_->getParent()->setVisible(false);
	switch (index)
	{
	case 1:
		break;
	case 2:
		OnPlayVoice(9, 1.3);
		break;
	case 3:
		OnPlayVoice(10, 2.5);
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case  7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	}
}
