#pragma once
class CVideoManager
{
public:
	CVideoManager();
	~CVideoManager();
	static CVideoManager* GetInstance();
private:
	static CVideoManager* Instance_;
};

