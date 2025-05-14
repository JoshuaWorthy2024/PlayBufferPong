#pragma once
#include "GameEntity.h"
#include "Config.h"

class Grid;
using std::vector;

class Npc;

class GridCell
{
public:
	GridCell(int row, int column);
	GridCell(int row, int column, Play::Vector2D position);

	void Add(GameEntity* entity);
	bool Remove(GameEntity* entity);
	bool MoveEntityFrom(GameEntity* entity, EDirection direction);

	const bool IsEmpty() const;
	const bool CanWalkOn() const;
	const bool CanSpawnOn() const;
	bool IsGridCell(int row, int column) const { return (row == m_Row) && (column == m_Column); }
	void AssignGrid(Grid* grid);
	Grid* GetGrid();
	const std::vector<GameEntity*> GetEntities() const { return m_Entities; }

	const int GetRow() const { return m_Row; }
	const int GetColumn() const { return m_Column; }
	void CheckBush();
	void SetWalkable(bool value);
	void SetNpc(Npc* npc)
	{
		m_Npc = npc;
	}
	Npc* GetNpc()
	{
		return m_Npc;
	}
private:
	int m_Row;
	int m_Column;
	Play::Vector2D m_Position;
	std::vector<GameEntity*> m_Entities;
	bool m_Walkable = false;
	Grid* m_Grid = nullptr;
	Npc* m_Npc = nullptr;
};

