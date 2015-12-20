#include "SkillData.h"


CSkillData::CSkillData()
{
}


CSkillData::~CSkillData()
{
}
void CSkillData::updateResouce()
{
	if (ResourceFrameCount1 == 0)
		ResourceName1 = "";
	if (ResourceFrameCount2 == 0)
		ResourceName2 = "";
	if (ResourceFrameCount3 == 0)
		ResourceName3 = "";
}