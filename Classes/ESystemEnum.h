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
#endif // !_ESYSTEMENUM_H_