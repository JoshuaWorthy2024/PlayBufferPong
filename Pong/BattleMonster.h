#pragma once

#include "string"
#include <Play.h>
#include "Config.h"

class WildMonster;
class CapturedMonster;
class Menu;
class HealthTrack;
class Battle;

class BattleMonster
{
public:
	BattleMonster(WildMonster* monster, Battle* battle);
	BattleMonster(CapturedMonster* monster, Battle* battle);
	~BattleMonster();

	void SetupMovesMenu(Menu* menu);

	void SetPosition(Play::Vector2D position);

	void Draw();

	void Update(float timeElapsed);

	void ActivateMove(int slot, BattleMonster& target);

	void SetFrame(int frame)
	{
		m_Frame = frame;
	}
	int GetFrame()
	{
		return m_Frame;
	}
	Play::Vector2D GetPosition()
	{
		return m_Position;
	}

	const int GetCurrentHealth();
	const int GetTotalHealth();
	HealthTrack* GetHealthTrack()
	{
		return m_HealthTrack;
	}

	void SetBattle(Battle* battle)
	{
		m_Battle = battle;
	}

	Battle* GetBattle()
	{
		return m_Battle;
	}
	FMonsterInfo GetMonsterInfo();

	void ActivateRandom(BattleMonster& attacker, BattleMonster& target);
private:
	void SetHealth(WildMonster* monster);
	void SetHealth(CapturedMonster* monster);

	Battle* m_Battle = nullptr;

	HealthTrack* m_HealthTrack = nullptr;

	std::string m_SpriteName;

	Play::Vector2D m_Position = { -1, -1 };

	int m_Frame = 0;

	EAttackSetHandlerConfig m_AttackKey;
};

