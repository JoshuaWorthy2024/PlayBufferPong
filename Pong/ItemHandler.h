#pragma once
#include "string"
#include "vector"

class GroundItem;
class Player;
class Grid;
class GridCell;

class ItemHandler
{
public:
	std::string GetItemName(int id);
	std::string GetSpriteName(int id);
	void PickupGroundItem(GridCell* cell);
	void AddGroundItem(int id, int amount, Grid* grid, int row, int column);
	void AddGroundItem(GroundItem* item, Grid* grid, int row, int column);
	void DrawAll();
	void UpdateAll(float elapsedTime);
	void CullGroundItems();
private:
	bool m_CullingItems = false;
	std::vector<GroundItem*> m_GroundItems;
	std::vector<GroundItem*> m_PendingGroundItemsToBeRemoved;
};

