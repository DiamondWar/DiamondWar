#pragma once
#include "cocos2d.h"
class CGameSceneControl
{
public:
	CGameSceneControl();
	~CGameSceneControl();
	static CGameSceneControl* GetInstance();
	void CreateSolider(int id, int ranks , float level);
	void CreateBoss(int ranks);
	void SetRoot(cocos2d::Node* root);
	void InitGameData();
	void CreateSpell(int id);
	bool IsHaveConsumeHero(int color ,int num);
	int IsHaveHero(int color, int num);
	void AddScreenShake();
	cocos2d::Node* GameRoot_;
	int HeroList[8];
private: 
	static CGameSceneControl* Instance_;
};

