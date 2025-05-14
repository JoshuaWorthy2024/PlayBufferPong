#pragma once
#include "vector"
#include "memory"
#include "Battle.h"

class Player;
class WildMonster;

class BattleHandler
{
public:
	BattleHandler();
	void CreateBattle(Player* player, WildMonster* enemy);
	void SetBattle(std::unique_ptr<Battle> battle)
	{
		m_Battle = std::move(battle);
	}
	std::unique_ptr<Battle>& GetBattle()
	{
		return m_Battle;
	}
private:
	std::unique_ptr<Battle> m_Battle;
};

