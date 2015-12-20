#pragma once
#ifndef _CSOLIDERDATA_H_
#define  _CSOLIDERDATA_H_
#include "cocos2d.h"
class CSoliderData :public cocos2d::Node
{
public:
	CSoliderData();
	~CSoliderData();

	int ID;  //Id
	std::string Name;  //名称
	int  SoliderType;   //类型
	int NeedStar;		//所需费用
	
	int AttackId;		//攻击id
	int SkillId;		//技能id
	float AttackRange;  // 射程
	int Attack;			//攻击力
	int Blood;			//血量
	float MoveSpeed;	//移动速度
	float AttackInterval; //攻击频率
	int StrengthValue;	//强化参数
	std::string ResourceName;	//资源名称
	float ScaleValue;		//缩放系数
	int RangeR;			//碰撞半径
	std::string Desc;	//描述信息

};
#endif 

