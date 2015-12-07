#pragma once
#ifndef _CBATTLEOBJECT_H_
#define  _CBATTLEOBJECT_H_


#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ESystemEnum.h"
class CBattleObject:public cocos2d::Node
{
public:
	int DownLoadType; 
	std::string ResourceName;
	std::string SkillName;
	int Init_x;//初始化位置
	int Init_y;
	//碰撞物体的半径
	int  RangeR_;

	//type为1时
	cocos2d::Node* Obj;
	cocostudio::timeline::ActionTimeline* _Action;
	//type为2时
	cocos2d::Animation Animation_;
	CBattleObject();
	~CBattleObject();
	virtual void OnResourceLoadComplete() = 0;
	virtual void OnAttackActionComplete() = 0;
	virtual void OnHurtActionComplete() = 0;
	virtual void OnSkillActionComplete() = 0;
	virtual void Update();
	void InitObj();
	virtual void OnHurt();
	virtual void OnIdle();
	virtual void OnRun();
	virtual void OnAttack();
	virtual void OnSkill();

	bool IsDelete_ = false;
private:
	EAction ActionType;
};
#endif // !_CBATTLEOBJECT_H_

