#pragma once
#include "cocos2d.h"
class CSkillData :public cocos2d::Node
{
public:
	CSkillData();
	~CSkillData();

	int ID;
	std::string Name;
	int TargetRank;//1Ϊ���Եз���Ч,2Ϊ�����ѷ���Ч,3Ϊ��˫������Ч
	int TargetType;//1Ϊ���Ե��浥λ(��ս��Զ��)��Ч,2Ϊ���Է��е�λ��Ч,3Ϊ���������͵�λ����Ч
	int BulletType;//����  �������������ĵ�������ID,û����������Ϊ0
	int BulletValue[3];//��������
	int HurtCf;
	int CoolTime;
	std::string AttributeInfo;
	int EffectId;
	int EffectCf;
	int EffectValue[3];
	std::string Desc;
	std::string ResourceName;
	int ResourceFrameCount;
};

