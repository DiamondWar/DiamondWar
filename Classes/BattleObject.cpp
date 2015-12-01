#include "BattleObject.h"
USING_NS_CC;

CBattleObject::CBattleObject()
{
}


CBattleObject::~CBattleObject()
{
}
 void CBattleObject::InitObj()
{
	 if (DownLoadType == 1)//直接加载csb文件
	 {
		 Obj = CSLoader::createNode(ResourceName+".csb");
		 _Action = CSLoader::createTimeline(ResourceName+".csb");
		 Obj->runAction(_Action);
		 OnResourceLoadComplete();
	 }
	 else if (DownLoadType == 2)//加载SpriteFrameCache中的资源
	 {
		 SpriteFrame* frame  = SpriteFrameCache::getInstance()->getSpriteFrameByName(ResourceName);
		 Obj = CCSprite::createWithSpriteFrame(frame);
		 OnResourceLoadComplete();
	 }
	 else if (DownLoadType == 3)//直接从路径中加载
	 {

	 }
}
 void CBattleObject::Update()
 {
	 if (DownLoadType == 1)
	 {
		 if (!_Action->isPlaying())
		 {
			 switch (ActionType)
			 {
			 case EAction_Idle:
				 break;
			 case EAction_Walk:
				 break;
			 case EAction_Attack:
				 OnAttackActionComplete();
				 break;
			 case EAction_Hurt:
				 OnHurtActionComplete();
				 break;
			 case EAction_Skill:
				 OnSkillActionComplete();
				 break;
			 default:
				 break;
			 }
		 }
	 }
	
	
 }
 void CBattleObject::OnIdle()
 {
	 ActionType = EAction_Idle;
	 if (DownLoadType == 1)
	 {
		 _Action->play("stand", true);
	 }
	 else if (DownLoadType == 1)
	 {

	 }
 }
 void CBattleObject::OnRun()
 {
	 ActionType = EAction_Walk;
	 if (DownLoadType == 1)
	 {
		 _Action->play("walk", true);
	 }
 }
 void CBattleObject::OnAttack()
 {
	 ActionType = EAction_Attack;
	 if (DownLoadType == 1)
	 {
		 _Action->play("attack", false);
	 }
 }
 void CBattleObject::OnSkill()
 {
	 ActionType = EAction_Skill;
	 if (DownLoadType == 1)
	 {
		 if (_Action->IsAnimationInfoExists("kill"))
		 {
			 _Action->play("kill", false);
		 }
		 else
		 {
			 _Action->play("attack", false);
		 }
		 
	 }
 }
 void CBattleObject::OnHurt()
 {
	 ActionType = EAction_Hurt;
	 if (DownLoadType == 1)
	 {
		 _Action->play("beattack", false);
	 }
 }

