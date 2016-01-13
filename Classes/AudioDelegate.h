#pragma once
class CAudioDelegate
{
public:
	virtual void OnAudioComplete(int index) = 0;
};
class ChoseTowerDelegate
{
public:
	virtual void OnChoseTower(int index, bool flag) = 0;
};
class TowerListDelegate
{
public:
	virtual void ClickTower(int index) =0;

};