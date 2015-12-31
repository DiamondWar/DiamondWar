#include "SpellData.h"


CSpellData::CSpellData()
{
}


CSpellData::~CSpellData()
{
}
void CSpellData::updateResouce()
{
	if (ResourceFrameCount1 == 0)
		ResourceName1 = "";
	if (ResourceFrameCount2 == 0)
		ResourceName2 = "";
	if (ResourceFrameCount3 == 0)
		ResourceName3 = "";
}