#pragma once
#include "cocos2d.h"
class CSkillData
{
public:
	CSkillData();
	~CSkillData();

	int ID;
	std::string Name;
	int TargetRank;//1为仅对敌方有效,2为仅对友方有效,3为对双方都有效
	int TargetType;//1为仅对地面单位(近战和远程)有效,2为仅对飞行单位有效,3为对所有类型单位都有效
	int BulletType;//弹道  发射出的抛射物的弹道类型ID,没有抛射物则为0
	std::string BulletValue;//弹道参数
	int HurtCf;
	int CoolTime;
	std::string AttributeInfo;
	int EffectId;
	int EffectCf;
	std::string EffectVale;
	std::string Desc;
};

