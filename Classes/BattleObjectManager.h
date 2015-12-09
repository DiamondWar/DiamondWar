#pragma once
#ifndef  _CBATTLEOBJECTMANGER_H_
#define _CBATTLEOBJECTMANGER_H_


#include "cocos2d.h"
#include "Solider.h"
#include "CGlobleConfig.h"
#include "Bullet.h"
#include "Buff.h"
#include "HurtShow.h"
 class CBattleObjectManager
{
public:
	CBattleObjectManager();
	~CBattleObjectManager();
	 static CBattleObjectManager* GetInstance();
	 void AddObject(CBattleObject* obj);
	 void AddBulletObject(CBullet* obj);
	 void AddHurtShowObject(CHurtShow* obj);
	 void AddBuffObject(CBuff*obj);
	 void DeleteObject(CBattleObject*obj);
	void DeleteObject(int id);
	void ClearAllObject();
	void Update();
	CSolider* GetEnemyByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetEnemyListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetFriendListByRange(float rank, float range, float r, float x, float y);
private:
	static CBattleObjectManager* Instance_;
	cocos2d::Vector<CBattleObject*> BattleList_;
	cocos2d::Vector<CBullet*> BulletList_;
	cocos2d::Vector<CHurtShow*> HurtShowList_;
	cocos2d::Vector<CBuff*> BuffList_;
};
#endif // ! _CBATTLEOBJECTMANGER_H_

