#pragma once
class CAudioManager
{
public:
	CAudioManager();
	~CAudioManager();
	static CAudioManager* GetInstance();
private: 
	static CAudioManager* Instance_;
};

