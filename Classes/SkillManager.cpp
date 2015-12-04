#include "SkillManager.h"
USING_NS_CC;

CSkillManager* CSkillManager::Instance_ = nullptr;
CSkillManager::CSkillManager()
{
}
CSkillManager* CSkillManager::GetInstance()
{
	if (Instance_ == nullptr)
		Instance_ = new CSkillManager();
	return Instance_;
}

CSkillManager::~CSkillManager()
{
}

void CSkillManager::ChoseSkill(CSkillData*data, CSolider* target)
{
	
	SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("n0001.png");
	CCSprite* Obj = CCSprite::createWithSpriteFrame(frame);
	Animation* ObjAction_ = AnimationCache::sharedAnimationCache()->getAnimation("Shifa");
	if (ObjAction_ == NULL)
	{
		Vector<SpriteFrame*> vsp;
		for (int i = 1; i <= 4; i++)
		{
			String *string = String::createWithFormat("n000%d.png", i);
			SpriteFrame *spfr = SpriteFrameCache::getInstance()->getSpriteFrameByName(string->getCString());
			vsp.pushBack(spfr);
		}
		Animation* ObjAction_ = Animation::createWithSpriteFrames(vsp, 1.0f / 12.0f);
		AnimationCache::sharedAnimationCache()->addAnimation(ObjAction_, "Shifa");
		Animate *animate = Animate::create(ObjAction_);
		auto *ac1 = Sequence::create(animate, NULL, NULL);
		Obj->runAction(ac1);
		target->Obj->addChild(Obj);
	}
	else
	{
		Animate *animate = Animate::create(ObjAction_);
		auto *ac1 = Sequence::create(animate, NULL, NULL);
		Obj->runAction(ac1);
		target->Obj->addChild(Obj);
	}
	
}
void CSkillManager::OnShiFaComplete()
{

}
