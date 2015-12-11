#pragma once
#include "cocos2d.h"
class CGameSceneControl
{
public:
	CGameSceneControl();
	~CGameSceneControl();
	static CGameSceneControl* GetInstance();
	void CreateSolider(int id, int ranks);
	void CreateBoss(int ranks);
	void SetRoot(cocos2d::Node* root);
	cocos2d::Node* GameRoot_;
private: 
	static CGameSceneControl* Instance_;
};

