#include "BattleMainMenuState.h"

#include "Play.h"
#include "BattleFightMenuState.h"
#include "Battle.h"
#include "BattleInventoryState.h"

BattleState* BattleMainMenuState::Handle()
{
	if (Play::KeyPressed(Play::KEY_1))
	{
		std::cout << "Pressed 1" << std::endl;
		m_Battle->ShowMovesMenu();
		return new BattleFightMenuState(parentPlayer, m_Friendly, m_Enemy, m_Battle);
	}
	else if (Play::KeyPressed(Play::KEY_2))
	{
		std::cout << "Pressed 2" << std::endl;
		m_Battle->ShowInventoryMenu();
		return new BattleInventoryState(parentPlayer, m_Friendly, m_Enemy, m_Battle);
	}
	else if (Play::KeyPressed(Play::KEY_3))
	{
		std::cout << "Pressed 3" << std::endl;
	}
	else if (Play::KeyPressed(Play::KEY_4))
	{
		std::cout << "Pressed 4" << std::endl;
	}
	else if (Play::KeyPressed(Play::KEY_BACKSPACE))
	{
		std::cout << "Exiting Fight Menu" << std::endl;
		m_Battle->ShowMainMenu();
		return new BattleMainMenuState(parentPlayer, m_Friendly, m_Enemy, m_Battle);
	}
	return this;
}

void BattleMainMenuState::Update()
{
   
}
