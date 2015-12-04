#include "Buff.h"
#include "CGlobleConfig.h"

CBuff::CBuff(CBuffData *data)
{
	BuffData = data;
	ResourceName = data->ResourceName;
	InitObj();
}

void CBuff::OnResourceLoadComplete()
{
	if (BuffData->AttackType == 1||BuffData->AttackType== 3)
	{
		Obj->setPosition(BuffData->init_x, BuffData->init_y);
		BuffData->From->getParent()->addChild(Obj);
	}
	else
	{
		Obj->setPosition(0,0);
		BuffData->Target->Obj->addChild(Obj);
	}
	StartTime = CCGlobleConfig::GetCurrntTime();
}
void CBuff::Update()
{
	NowTime = CCGlobleConfig::GetCurrntTime();
	if (NowTime > StartTime + BuffData->ContinueTime)
	{
		//buf��ʧ
		Obj->setVisible(false);
		this->release();
	}
	else
	{
		if (NowTime > LastTime + BuffData->InveralTime)
		{
			//���ʱ�䵽�� ��������˺�
			LastTime = NowTime;

		}
	}
}
CBuff::~CBuff()
{
	
	Obj->release();
}
