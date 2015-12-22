#include "SoliderDie.h"
#include "CGlobleConfig.h"
#include "GameSceneControl.h"

USING_NS_CC;

CSoliderDie::CSoliderDie()
{
}
CSoliderDie::~CSoliderDie()
{
	
}
void CSoliderDie::SetFont(int type)
{
}
void CSoliderDie::ShowLabel(int value, CSolider* node)
{
	int n = 0;
	if (value == 1)
	{
		Sprite_ = Sprite::createWithSpriteFrameName("medie.png");
	}
	else
	{
		Sprite_ = Sprite::createWithSpriteFrameName("enmeydie.png");
	}
	CGameSceneControl::GetInstance()->GameRoot_->addChild(Sprite_);
	Sprite_->setPosition(node->CenterPoint_->getPosition() + node->Obj->getPosition());
	isMove = true;
}
void CSoliderDie::Update()
{
	if (CCGlobleConfig::Game_time % 3 == 0&&isMove == true)
	{
		MoveNum++;
		Sprite_->setPositionY(Sprite_->getPositionY() + 1);
		if (MoveNum > 20)
		{
			isMove = false;
			IsDelete_ = true;
			Sprite_->setVisible(false);
			this->release();
		}
	}


}
