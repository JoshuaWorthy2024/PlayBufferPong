#include "CapturedMonster.h"

#include "HealthTrack.h"
#include "AttackSetHandler.h"
#include <iostream>

CapturedMonster::CapturedMonster(FMonsterInfo monsterInfo, GameEntity* owner, int level)
{
	m_Owner = owner;
	m_Name = monsterInfo.MonsterName;
	m_SpriteName = monsterInfo.WildSpriteName;
	m_Experience = 0;
	m_Level = level;
	m_HealthTrack = new HealthTrack(monsterInfo.Health);
	attackSet = AttackSetHandler::GetInstance().GetAttackSet(monsterInfo.ashc);
	m_MonsterInfo = monsterInfo;
}

CapturedMonster::~CapturedMonster()
{
	std::cout << std::endl << "Deleting Captured monster" << std::endl;
}

const int CapturedMonster::GetTotalHealth()
{
	if (m_HealthTrack)
	{
		return m_HealthTrack->GetTotal();
	}
	return -1;
}

const int CapturedMonster::GetCurrentHealth()
{
	if (m_HealthTrack)
	{
		return m_HealthTrack->GetCurrent();
	}
	return -1;
}
