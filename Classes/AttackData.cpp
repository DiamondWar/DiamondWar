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
		ResourceName2 = "";
	if (ResourceFrameCount3 == 0)
		ResourceName3 = "";
}