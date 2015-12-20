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
	int TargetRank;//�����ڵ������� ��1Ϊ���� 2Ϊ�Ѿ� 3Ϊ˫������Ч
	int TargetType;  //���õ�Ӣ������ 1Ϊ���沿�� 2Ϊ���в��� 3Ϊ���߶���
	int  AttackPoint; //����㣬���в�λ
	int BulletType; //��������
	int BulletValue[3]; //��������
	int  EffectId;	//��Я����buff��Ч
	int EffectValue; //buff����
	std::string ResourceName1;//��Դ1
	int ResourceFrameCount1; //֡��
	std::string ResourceName2;//��Դ2
	int ResourceFrameCount2; //֡��
	std::string ResourceName3;//��Դ3
	int ResourceFrameCount3; //֡��
	std::string AttackVoice; //������Ч
	std::string HitVoice;//������Ч

	void updateResouce();
};