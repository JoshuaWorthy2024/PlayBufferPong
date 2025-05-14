#include "Inventory.h"
#include "InventoryItem.h"
#include "Game.h"
#include <iostream>
#include "ItemHandler.h"
#include "Menu.h"

void Inventory::Add(int id, int amount)
{
	InventoryItem* item = new InventoryItem(id, amount);
	m_Items.push_back(item);
	std::cout << "Added " << Game::GetInstance().GetItemHandler()->GetItemName(id) << " x" << amount << " to your inventory." << std::endl;
}

void Inventory::PrintItems()
{
	if (m_Items.empty())
	{
		std::cout << std::endl << "You do not have any items in your inventory." << std::endl << std::endl;
		return;
	}
	int i = 1;
	std::cout << "[START OF INVENTORY]" << std::endl;
	for (InventoryItem* item : m_Items)
	{
		std::cout << i << ") Item: " << Game::GetInstance().GetItemHandler()->GetItemName(item->GetId()) << " | Amount: " << item->GetAmount() << std::endl;
		i++;
	}

	std::cout << "[END OF INVENTORY]" << std::endl << std::endl;
}

void Inventory::SetupInventoryMenu(Menu* menu)
{
	int x = MENU_FIRST_X;
	int y = MENU_FIRST_Y;

	int offset = 60;

	for (int i = 0; i < m_Items.size(); i++)
	{
		if (i == 2)
		{
			x = MENU_SECOND_X;
			y = MENU_SECOND_Y;
		}

		std::cout << i << ") Item Menu: " << Game::GetInstance().GetItemHandler()->GetItemName(m_Items.at(i)->GetId()) << " | Amount: " << m_Items.at(i)->GetAmount() << std::endl;

		switch (i)
		{
			case 0:
			case 2:
				menu->Add(std::to_string(i + 1) + ") " + Game::GetInstance().GetItemHandler()->GetItemName(m_Items.at(i)->GetId()), x, y, 0, 0);
				break;
			case 1:
			case 3:
				menu->Add(std::to_string(i + 1) + ") " + Game::GetInstance().GetItemHandler()->GetItemName(m_Items.at(i)->GetId()), x, y, 0, offset);
				break;
		}
	}
}

InventoryItem* Inventory::GetInventoryItem(int slot)
{ 
	return m_Items.at(slot);
}
