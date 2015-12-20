#pragma once
#include "cocos2d.h"
class CAttackData :
	public cocos2d::Node
{
public:
	CAttackData();
	~CAttackData();
	int ID;  //id
	std::string Name;
	int TargetRank;//作用在敌友身上 ，1为敌人 2为友军 3为双方都有效
	int TargetType;  //作用的英雄类型 1为地面部队 2为空中部队 3为两者都有
	int  AttackPoint; //打击点，命中部位
	int BulletType; //弹道类型
	int BulletValue[3]; //弹道参数
	int  EffectId;	//所携带的buff特效
	int EffectValue; //buff参数
	std::string ResourceName1;//资源1
	int ResourceFrameCount1; //帧数
	std::string ResourceName2;//资源2
	int ResourceFrameCount2; //帧数
	std::string ResourceName3;//资源3
	int ResourceFrameCount3; //帧数
	std::string AttackVoice; //攻击音效
	std::string HitVoice;//命中音效

	void updateResouce();
};