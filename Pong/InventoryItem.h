#pragma once
class InventoryItem
{
public:
	InventoryItem(int id, int amount);
	int GetId()
	{
		return m_Id;
	}
	int GetAmount()
	{
		return m_Amount;
	}
	bool IsPokeBall();
private:
	int m_Id = -1;
	int m_Amount = 0;
};

