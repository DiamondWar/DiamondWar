#pragma once
#ifndef  _CBATTLEOBJECTMANGER_H_
#define _CBATTLEOBJECTMANGER_H_


#include "cocos2d.h"
#include "Solider.h"
#include "CGlobleConfig.h"
 class CBattleObjectManager
{
public:
	CBattleObjectManager();
	~CBattleObjectManager();
	 static CBattleObjectManager* GetInstance();
	 void AddObject(CBattleObject* obj);
	 void DeleteObject(CBattleObject*obj);
	void DeleteObject(int id);
	void ClearAllObject();
	void Update();
	CSolider* GetEnemyByRange(float rank, float range, float r, float x, float y);
private:
	static CBattleObjectManager* Instance_;
	cocos2d::Vector<CBattleObject*> BattleList_;
};
#endif // ! _CBATTLEOBJECTMANGER_H_

