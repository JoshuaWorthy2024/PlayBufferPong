#include "BattleInventoryState.h"

#include "Play.h"
#include "Battle.h"
#include "BattleMainMenuState.h"
#include "Game.h"
#include "Player.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "ItemHandler.h"

BattleState* BattleInventoryState::Handle()
{
	if (Play::KeyPressed(Play::KEY_BACKSPACE))
	{
		std::cout << "Exiting Inventory Menu" << std::endl;
		m_Battle->ShowMainMenu();
		return new BattleMainMenuState(parentPlayer, m_Friendly, m_Enemy, m_Battle);
	}

    if (Play::KeyPressed(Play::KEY_1) || Play::KeyPressed(Play::KEY_2) || Play::KeyPressed(Play::KEY_3) ||
        Play::KeyPressed(Play::KEY_4))
    {
        Player* player = Game::GetInstance().GetPlayer();
        InventoryItem* item = nullptr;
        if (Play::KeyPressed(Play::KEY_1))
        {
             item = player->GetInventory()->GetInventoryItem(0);
        }
        else if (Play::KeyPressed(Play::KEY_2))
        {
            item = player->GetInventory()->GetInventoryItem(1);
        }
        else if (Play::KeyPressed(Play::KEY_3))
        {
            item = player->GetInventory()->GetInventoryItem(2);
        }
        else if (Play::KeyPressed(Play::KEY_4))
        {
            item = player->GetInventory()->GetInventoryItem(3);
        }

        if (item != nullptr)
        {
            if (item->IsPokeBall())
            {
                m_Battle->CaptureEnemy(item);
            }
        }
        else
        {
            std::cout << "Item was null." << std::endl;
        }
    }

	return this;
}

void BattleInventoryState::Update()
{

}
