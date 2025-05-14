#include "InventoryItem.h"

#include "Game.h"
#include "ItemHandler.h"

InventoryItem::InventoryItem(int id, int amount)
{
	m_Id = id;
	m_Amount = amount;
}

bool InventoryItem::IsPokeBall()
{
	if (m_Id == 0 || m_Id == 1 || m_Id == 2)
	{
		return true;
	}

	return false;
}
