#pragma once
#ifndef  _CBATTLEOBJECTMANGER_H_
#define _CBATTLEOBJECTMANGER_H_


#include "cocos2d.h"
#include "BaseBoss.h"
#include "CGlobleConfig.h"
#include "Bullet.h"
#include "Buff.h"
#include "HurtShow.h"
#include "BaseBoss.h"
#include "SoliderDie.h"
 class CBattleObjectManager
{
public:
	CBattleObjectManager();
	~CBattleObjectManager();
	 static CBattleObjectManager* GetInstance();
	 void AddObject(CBattleObject* obj);
	 void AddBulletObject(CBattleObject* obj);
	 void AddHurtShowObject(CHurtShow* obj);
	 void AddSoliderDie(CSoliderDie* obj);
	 void AddBuffObject(CBuff*obj);
	 void DeleteObject(CBattleObject*obj);
	 void SetFirstRanksBoss(CBaseBoss* boss);
	 void SetSecondRanksBoss(CBaseBoss* boss);
	 CBaseBoss* GetSecondRanksBoss();
	 CBaseBoss* GetFirstRanksBoss();
	void DeleteObject(int id);
	void ClearAllObject();
	void Update();

	CBaseBoss* GetEnemyByRange(float rank, int type, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetEnemyListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetLuDiEnemyListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetFeiXingEnemyListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetFriendListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetLuDiFriendListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetFeiXingFriendListByRange(float rank, float range, float r, float x, float y);
	cocos2d::Vector<CSolider*> GetSoliderListByRange(int type,float range, float r, float x, float y);
private:
	static CBattleObjectManager* Instance_;
	cocos2d::Vector<CBattleObject*> BattleList_;
	cocos2d::Vector<CBattleObject*> BulletList_;
	cocos2d::Vector<CHurtShow*> HurtShowList_;
	cocos2d::Vector<CSoliderDie*> SoliderDieList_;
	cocos2d::Vector<CBuff*> BuffList_;
	CBaseBoss* FirstRanksBoss_ = nullptr;
	CBaseBoss* SecondRanksBoss_ = nullptr;
};
#endif // ! _CBATTLEOBJECTMANGER_H_

