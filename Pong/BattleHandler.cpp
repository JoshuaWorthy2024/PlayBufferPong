#include "BattleHandler.h"

#include "WildMonster.h"
#include "Battle.h"

BattleHandler::BattleHandler()
{
	std::cout << "Created battle handler" << std::endl;
}

void BattleHandler::CreateBattle(Player* player, WildMonster* enemy)
{
	if (!m_Battle)
	{
		m_Battle = std::make_unique<Battle>();
		m_Battle->Start(player, enemy);
	}
}
