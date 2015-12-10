//���ƽ�ɫ�Ĳ�����ö��
#ifndef _ESYSTEMENUM_H_
#define  _ESYSTEMENUM_H_


enum ESoliderOpreate
{
	ESoliderOpreate_Idle = 0,
	ESoliderOpreate_Walk,
	ESoliderOpreate_Attack,
	ESoliderOpreate_Skill,
	ESoliderOpreate_Hurt,
};
//���ƶ����Ĳ���
enum EAction
{
	EAction_Idle = 0,
	EAction_Walk,
	EAction_Attack,
	EAction_Hurt,
	EAction_Skill,
};
//��������
enum ESoliderType
{
	E_Solider_MT =1,
	E_Solider_YC,
	E_Solider_FX,
};
enum ESoliderAttackType
{
	E_Solider_Enemy = 1,
	E_Solider_Friend,
	E_solider_EAF,
};
enum EAttackTarget
{
	E_Target_Floor= 1,//ֻ�Ե��湥��
	E_Target_Sky,//ֻ����չ���
	E_Target_Both,//��պ͵��涼��
};
enum EBulletType
{
	E_Bullet_None =0,
	E_Bullet_GenZong,
	E_Bullet_FanWei,
	E_Bullet_Line,
	E_Bullet_PaoWuXian,
	E_Bullet_ChuiZhi,
};
enum EBuffType
{
	E_Buff_None = 0,
	E_Buff_LowSpeed,//�����ƶ��ٶ�
	E_Buff_HighSpeed,//�����ƶ��ٶ�
	E_Buff_LowAttackSpeed,//���ٹ����ٶ�
	E_Buff_HighAttackSpeed,//���ӹ����ٶ�
	E_Buff_LowAttack,//���ٹ�����
	E_Buff_HighAttack,//���ӹ�����
	E_Buff_NoAction,//ֹͣһ�й����ƶ�
	E_Buff_LowBlood,//����Ѫ��
	E_Buff_HighBlood,//����Ѫ��
	E_Buff_LowBloodUp,//����Ѫ������
	E_Buff_HighBloodUp,//����Ѫ������
};
#endif // !_ESYSTEMENUM_H_