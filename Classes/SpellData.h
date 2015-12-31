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
	int TargetRank;//1Ϊ���Եз���Ч,2Ϊ�����ѷ���Ч,3Ϊ��˫������Ч
	int TargetType;//1Ϊ���Ե��浥λ(��ս��Զ��)��Ч,2Ϊ���Է��е�λ��Ч,3Ϊ���������͵�λ����Ч
	float Hurt;//�˺�ֵ
	int CoolTime;
	int AttackPoint;//���в�λ
	int BulletType;//����  �������������ĵ�������ID,û����������Ϊ0
	float BulletValue[3];//��������
	int EffectId;
	float EffectValue[3];
	std::string ResourceName1;//��Դ1
	int ResourceFrameCount1; //֡��
	std::string ResourceName2;//��Դ2
	int ResourceFrameCount2; //֡��
	std::string ResourceName3;//��Դ3
	int ResourceFrameCount3; //֡��

	std::string AttackVoice; //������Ч
	std::string HitVoice;//������Ч
	std::string Desc;
	void updateResouce();
};
