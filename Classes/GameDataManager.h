#pragma once
class CGameDataManager
{
public:
	CGameDataManager();
	~CGameDataManager();
	static CGameDataManager* GetInstance();
private: 
	static CGameDataManager* Instance_;
};

