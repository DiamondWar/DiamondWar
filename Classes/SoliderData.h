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
	std::string Name;  //����
	int  SoliderType;   //����
	int NeedStar;		//�������
	
	int AttackId;		//����id
	int SkillId;		//����id
	float AttackRange;  // ���
	int Attack;			//������
	int Blood;			//Ѫ��
	float MoveSpeed;	//�ƶ��ٶ�
	float AttackInterval; //����Ƶ��
	int StrengthValue;	//ǿ������
	std::string ResourceName;	//��Դ����
	float ScaleValue;		//����ϵ��
	int RangeR;			//��ײ�뾶
	std::string Desc;	//������Ϣ

};
#endif 

