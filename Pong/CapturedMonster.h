#pragma once
#include "string"
#include "Config.h"
#include "memory"

class HealthTrack;
class AttackSet;
class GameEntity;

class CapturedMonster
{
public:
	CapturedMonster(FMonsterInfo monsterInfo, GameEntity* owner, int level);
	~CapturedMonster();
	std::string GetSpriteName()
	{
		return m_SpriteName;
	}
	FMonsterInfo GetMonsterInfo()
	{
		return m_MonsterInfo;
	}

	const int GetTotalHealth();
	const int GetCurrentHealth();
	HealthTrack* GetHealthTrack()
	{
		return m_HealthTrack;
	}
private:
	GameEntity* m_Owner = nullptr;
	std::string m_Name;
	std::string m_SpriteName;
	int m_Experience;
	int m_Level;
	HealthTrack* m_HealthTrack = nullptr;
	std::shared_ptr<AttackSet> attackSet = nullptr;
	FMonsterInfo m_MonsterInfo;
};


