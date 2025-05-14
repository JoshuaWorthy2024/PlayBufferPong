#include "BattleState.h"

BattleState::BattleState(Player* player, BattleMonster* friendly, BattleMonster* enemy, Battle* battle)
{
	parentPlayer = player;
	m_Friendly = friendly;
	m_Enemy = enemy;
	m_Battle = battle;
}

