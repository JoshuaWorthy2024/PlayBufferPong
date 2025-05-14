#pragma once
#include "vector"

class InventoryItem;
class Menu;

class Inventory
{
public:
	void Add(int id, int amount);
	void PrintItems();
	void SetupInventoryMenu(Menu* menu);
	InventoryItem* GetInventoryItem(int slot);
private:
	std::vector<InventoryItem*> m_Items;
};

