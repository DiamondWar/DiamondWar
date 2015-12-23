#include "AttackData.h"


CAttackData::CAttackData()
{
}


CAttackData::~CAttackData()
{
}

void CAttackData::updateResouce()
{
	if (ResourceFrameCount1 == 0)
		ResourceName1 = "";
	if (ResourceFrameCount2 == 0)
	{
		ResourceFrameCount2 = 1;
		ResourceName2 = "Bullet_common_1";
		
	}
	
	if (ResourceFrameCount3 == 0)
		ResourceName3 = "";
}