#pragma once
#ifndef _CSOLIDERCONFIG_H_

#define _CSOLIDERCONFIG_H_
#include "cocos2d.h"
#include "SoliderData.h"
class CSoliderConfig
{
public:
	CSoliderConfig();
	~CSoliderConfig();

	void LoadText();
	static CSoliderConfig* GetInstance();
	CSoliderData* GetItemById(int id);
	cocos2d::Vector<CSoliderData*> DataList_;
private: 
	std::string  StressText = "Solider_Config.txt";
	static CSoliderConfig* Instance_;
	
	
};
#endif 
