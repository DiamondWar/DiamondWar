//控制角色的操作的枚举
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
//控制动画的播放
enum EAction
{
	EAction_Idle = 0,
	EAction_Walk,
	EAction_Attack,
	EAction_Hurt,
	EAction_Skill,
};
//兵种类型
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
	E_Target_Floor= 1,//只对地面攻击
	E_Target_Sky,//只对天空攻击
	E_Target_Both,//天空和地面都打
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
	E_Buff_LowSpeed,//减少移动速度
	E_Buff_HighSpeed,//增加移动速度
	E_Buff_LowAttackSpeed,//减少攻击速度
	E_Buff_HighAttackSpeed,//增加攻击速度
	E_Buff_LowAttack,//减少攻击力
	E_Buff_HighAttack,//增加攻击力
	E_Buff_NoAction,//停止一切攻击移动
	E_Buff_LowBlood,//增加血量
	E_Buff_HighBlood,//减少血量
	E_Buff_LowBloodUp,//减少血量上限
	E_Buff_HighBloodUp,//增加血量上限
};
#endif // !_ESYSTEMENUM_H_