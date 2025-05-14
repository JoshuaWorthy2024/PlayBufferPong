#pragma once
#include "GridCell.h"
#include "CustomMap.h"
#include "Tile.h"
#include "string"

enum ETypeOfGrid
{
	GRID_NONE = 0,
	GRID_MAIN,
	GRID_HOSPITAL,
	GRID_SHOP,
	GRID_STARTER_HOUSE,
};

class Player;
class GroundItem;

class Grid

{
public:
	Grid(int rows, int columns, int startingX, int startingY, int spaceForRows, int spaceForColumns, std::string name, ETypeOfGrid type);

	void Initialize();
	bool Populate(int x, int y, GameEntity* entity);
	void Depopulate(int x, int y);

	bool IsPopulated(int x, int y);
	Play::Vector2D GetNewPosition(int x, int y, EDirection direction);
	const std::vector<GridCell*> GetCells() const { return m_Cells; }

	Play::Vector2D GridToWorldPosition(int row, int col)
	{
		float x = col * CELL_WIDTH + GRID_OFFSET_X;
		float y = row * CELL_HEIGHT + GRID_OFFSET_Y;
		return Play::Vector2D(x, y);
	}

	Play::Vector2D WorldToGridPosition(Play::Vector2D pos)
	{
		int col = (pos.x - GRID_OFFSET_X) / CELL_WIDTH;
		int row = (pos.y - GRID_OFFSET_Y) / CELL_HEIGHT;
		return { row, col };
	}
	const int GetRows() const { return m_Rows; }
	const int GetColumns() const { return m_Columns; }

	bool Move(GameEntity* entity, EDirection direction);

	bool IsNotBush();
	Tile* CreateTile(std::string spriteName, int row, int column, bool walkable);
	void DrawTiles(Player* player);
	bool IsNearby(Play::Vector2D pos1, Play::Vector2D pos2, int length);
	bool IsNearby(GridCell& cell1, GridCell& cell2, int rowBoundary, int colBoundary);
	bool IsNearby(GridCell& cell1, int currentRow, int currentCol, int rowBoundary, int colBoundary);
	bool IsNearby(Play::Vector2D pos1, Play::Vector2D pos2, int w, int h);

	void SetActive(bool value)
	{
		m_Active = value;
	}

	bool IsActive()
	{
		return m_Active;
	}
	void SetOrigin(Player* player);

	std::string GetName()
	{
		return m_Name;
	}
	Tile* GetTileAtPosition(int x, int y);
	GridCell* GetCellAtPosition(int x, int y);
	void SetOrigin(int row, int col);
	bool MakeGroundItem(GroundItem* item, int row, int column);
private:
	int m_Rows;
	int m_Columns;
	int m_StartingX;
	int m_StartingY;
	int m_SpaceForRows;
	int m_SpaceForColumns;

	bool m_Active = false;

	std::vector<GridCell*> m_Cells;
	CustomMap m_Populated_Cells;
	std::vector<Tile*> m_Tiles;
	std::string m_Name;

	const int CELL_WIDTH = 32;
	const int CELL_HEIGHT = 32;

	const int GRID_OFFSET_X = 50;
	const int GRID_OFFSET_Y = 50;

	ETypeOfGrid m_GridType = GRID_NONE;
	int m_Origin_Row = 0;
	int m_Origin_Col = 0;
};

