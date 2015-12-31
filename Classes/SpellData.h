#pragma once
#include "cocos2d.h"
class CSpellData: public cocos2d::Node
{
public:
	CSpellData();
	~CSpellData();

	int ID;
	std::string Name;
	int NeedStar_;
	int TargetRank;//1为仅对敌方有效,2为仅对友方有效,3为对双方都有效
	int TargetType;//1为仅对地面单位(近战和远程)有效,2为仅对飞行单位有效,3为对所有类型单位都有效
	float Hurt;//伤害值
	int CoolTime;
	int AttackPoint;//命中部位
	int BulletType;//弹道  发射出的抛射物的弹道类型ID,没有抛射物则为0
	float BulletValue[3];//弹道参数
	int EffectId;
	float EffectValue[3];
	std::string ResourceName1;//资源1
	int ResourceFrameCount1; //帧数
	std::string ResourceName2;//资源2
	int ResourceFrameCount2; //帧数
	std::string ResourceName3;//资源3
	int ResourceFrameCount3; //帧数

	std::string AttackVoice; //攻击音效
	std::string HitVoice;//命中音效
	std::string Desc;
	void updateResouce();
};
