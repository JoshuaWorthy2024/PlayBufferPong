#include "Grid.h"
#include "Tile.h"
#include <cmath>
#include "Player.h"
#include "Game.h"
#include "Hospital.h"
#include "Shop.h"
#include "StarterHouse.h"
#include "GroundItem.h"

Grid::Grid(int rows, int columns, int startingX, int startingY, int spaceForRows, int spaceForColumns, std::string name, ETypeOfGrid type)
{
	m_Rows = rows;
	m_Columns = columns;
	m_StartingX = startingX;
	m_StartingY = startingY;
	m_SpaceForColumns = spaceForColumns;
	m_SpaceForRows = spaceForRows;
	m_Name = name;
	m_GridType = type;
}

void Grid::Initialize()
{
	for (int r = (m_Rows * -1); r < m_Rows; r++)
	{
		for (int c = (m_Columns * -1); c < m_Columns; c++)
		{
			GridCell* gridCell = new GridCell(r, c, GridToWorldPosition(r, c));
			gridCell->AssignGrid(this);
			m_Cells.push_back(gridCell);
			m_Populated_Cells.Add(r, c, false);
		}
	}
}

bool Grid::Populate(int x, int y, GameEntity* entity)
{
	for (std::vector<GridCell*>::iterator it = m_Cells.begin(); it != m_Cells.end(); it++)
	{
		if ((*it))
		{
			if ((*it)->IsGridCell(x, y))
			{
				if (m_Populated_Cells.Update(x, y, true))
				{
					(*it)->Add(entity);
					return true;
				}
			}
		}
	}

	return false;
}

void Grid::Depopulate(int x, int y)
{
	for (std::vector<GridCell*>::iterator it = m_Cells.begin(); it != m_Cells.end(); it++)
	{
		if ((*it))
		{
			if ((*it)->IsGridCell(x, y))
			{
				m_Populated_Cells.Update(x, y, false);
				break;
			}
		}
	}
}

bool Grid::IsPopulated(int x, int y)
{
	if (m_Populated_Cells.GetMapInsert(x, y) == nullptr)
	{
		return false;
	}

	return m_Populated_Cells.GetMapInsert(x, y)->GetValue();
}

Play::Vector2D Grid::GetNewPosition(int x, int y, EDirection direction)
{
	Play::Vector2D newPosition(x, y);
	switch (direction)
	{
		case GRID_UP:
		{
			newPosition.x++;
			break;
		}
		case GRID_DOWN:
		{
			newPosition.x--;
			break;
		}
		case GRID_LEFT:
		{
			newPosition.y--;
			break;
		}
		case GRID_RIGHT:
		{
			newPosition.y++;
			break;
		}
	}
	return newPosition;
}

bool Grid::Move(GameEntity* entity, EDirection direction)
{
	Play::Vector2D currentGridPosition = WorldToGridPosition(entity->GetPosition());
	
	Play::Vector2D newGridPosition = GetNewPosition(currentGridPosition.x, currentGridPosition.y, direction);
	
	std::cout << "Current Grid: " << currentGridPosition.x << ", " << currentGridPosition.y << std::endl;
	std::cout << "New Grid: " << newGridPosition.x << ", " << newGridPosition.y << std::endl << std::endl;

	GridCell* nextCell = GetCellAtPosition(newGridPosition.x, newGridPosition.y);

	if (nextCell)
	{
		if (!nextCell->CanWalkOn())
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	if (m_GridType == GRID_MAIN)
	{
		if (Game::GetInstance().GetHospital()->CannotWalkOn(newGridPosition.x, newGridPosition.y))
		{
			return false;
		}
		if (Game::GetInstance().GetShop()->CannotWalkOn(newGridPosition.x, newGridPosition.y))
		{
			return false;
		}
		if (Game::GetInstance().GetStarterHouse()->CannotWalkOn(newGridPosition.x, newGridPosition.y))
		{
			return false;
		}
	}
	if (m_GridType == GRID_HOSPITAL)
	{
		if (newGridPosition.x == 0 && newGridPosition.y == 0)
		{
			// leave hospital
			Game::GetInstance().GetHospital()->Leave();
			return false;
		}
	}

	if (m_GridType == GRID_SHOP)
	{
		if (newGridPosition.x == 0 && newGridPosition.y == 0)
		{
			// leave hospital
			Game::GetInstance().GetShop()->Leave();
			return false;
		}
	}

	if (m_GridType == GRID_STARTER_HOUSE)
	{
		if (newGridPosition.x == 0 && newGridPosition.y == 0)
		{
			Game::GetInstance().GetStarterHouse()->Leave();
			return false;
		}
	}
	if (!m_Populated_Cells.DoesExist(newGridPosition.x, newGridPosition.y))
	{
		m_Populated_Cells.Add(newGridPosition.x, newGridPosition.y, true);
	}
	else
	{
		if (entity->GetGridCell()->MoveEntityFrom(entity, direction))
		{
			Depopulate(currentGridPosition.x, currentGridPosition.y);
		}
	}
	
	Populate(newGridPosition.x, newGridPosition.y, entity);

	return true;
}

bool Grid::IsNotBush()
{
	return false;
}

Tile* Grid::CreateTile(std::string spriteName, int row, int column, bool walkable)
{
	GridCell* cell = GetCellAtPosition(row, column);
	if (cell)
	{
		cell->SetWalkable(walkable);
		Play::Vector2D position = GridToWorldPosition(row, column);
		Tile* tile = new Tile(spriteName, position);
		m_Tiles.push_back(tile);
		return tile;
	}
	else
	{
		return nullptr;
	}
}

void Grid::DrawTiles(Player* player)
{
	for (std::vector<Tile*>::iterator it = m_Tiles.begin(); it != m_Tiles.end(); it++)
	{
		if (player)
		{
			if (*it)
			{
				if (IsNearby(player->GetPosition(), (*it)->GetPosition(), DRAW_LENGTH))
				{
					(*it)->Draw();
					Play::Vector2D vector = WorldToGridPosition((*it)->GetPosition());
				}
				else
				{
					continue;
				}
				
			}
		}
	}
}

bool Grid::IsNearby(Play::Vector2D pos1, Play::Vector2D pos2, int length)
{
	int distanceX = std::abs(pos1.x - pos2.x);
	int distanceY = std::abs(pos1.y - pos2.y);
	return (distanceX <= length && distanceY <= length);
}

bool Grid::IsNearby(GridCell& cell1, GridCell& cell2, int rowBoundary, int colBoundary)
{
	int rowDiff = 0;
	int colDiff = 0;

	if (cell1.GetRow() >= cell2.GetRow())
	{
		rowDiff = cell1.GetRow() - cell2.GetRow();
	}
	else
	{
		rowDiff = cell2.GetRow() - cell1.GetRow();
	}

	if (cell1.GetColumn() >= cell2.GetColumn())
	{
		colDiff = cell1.GetColumn() - cell2.GetColumn();
	}
	else
	{
		colDiff = cell2.GetColumn() - cell1.GetColumn();
	}

	if (rowDiff <= rowBoundary)
	{
		return true;
	}
	if (colDiff <= colBoundary)
	{
		return true;
	}
	return false;
}

bool Grid::IsNearby(GridCell& cell1, int currentRow, int currentCol, int rowBoundary, int colBoundary)
{
	int rowDiff = std::abs(cell1.GetRow() - currentRow);
	int colDiff = std::abs(cell1.GetColumn() - currentCol);

	if (rowDiff <= rowBoundary && colDiff <= colBoundary)
	{
		return true; // Inside the blocked area
	}
	return false; // Outside the blocked area
}

bool Grid::IsNearby(Play::Vector2D pos1, Play::Vector2D pos2, int w, int h)
{
	Play::Vector2D playerGridPosition = WorldToGridPosition(pos1);
	Play::Vector2D otherGridPosition = WorldToGridPosition(pos2);

	int dx = abs(playerGridPosition.x - otherGridPosition.x);
	int dy = abs(playerGridPosition.y - otherGridPosition.y);

	return (dx <= w && dy <= h);  // Rectangle shape
}

void Grid::SetOrigin(Player* player)
{
	for (GridCell* cell : m_Cells)
	{
		if (cell->GetRow() == m_Origin_Row && cell->GetColumn() == m_Origin_Col)
		{
			if (player->GetGridCell())
			{
				player->GetGridCell()->Remove(player);
			}
			EntityHandler::GetInstance().Add(this, m_Origin_Row, m_Origin_Col, player);
			break;
		}
	}
}

Tile* Grid::GetTileAtPosition(int x, int y)
{
	for (Tile* tile : m_Tiles)
	{
		if (tile->GetPosition().x == x && tile->GetPosition().y == y)
		{
			return tile;
		}
	}
}

GridCell* Grid::GetCellAtPosition(int x, int y)
{
	for (GridCell* cell : m_Cells)
	{
		if (cell->GetRow() == x && cell->GetColumn() == y)
		{
			return cell;
		}
	}

	return nullptr;
}

void Grid::SetOrigin(int row, int col)
{
	m_Origin_Row = row;
	m_Origin_Col = col;
}

bool Grid::MakeGroundItem(GroundItem* item, int row, int column)
{
	if (GridCell* cell = GetCellAtPosition(row, column))
	{
		item->SetGridCell(cell);
		Play::Vector2D pos = GridToWorldPosition(row, column);
		item->SetPosition(pos);
		return true;
	}
	return false;
}
