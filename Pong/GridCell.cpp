#include "GridCell.h"

#include "GameEntity.h"
#include "EntityHandler.h"
#include "Grid.h"
#include "Game.h"
#include "BattleHandler.h"
#include "Player.h"
#include "HealthTrack.h"
#include "Npc.h"

using std::vector;
GridCell::GridCell(int row, int column)
{
	m_Row = row;
	m_Column = column;
}

GridCell::GridCell(int row, int column, Play::Vector2D position)
{
    m_Row = row;
    m_Column = column;
    m_Position = position;
}

void GridCell::Add(GameEntity* entity)
{
    if (entity->GetEntityType() == NPC)
    {
        m_Npc = dynamic_cast<Npc*>(entity);
    }
	m_Entities.push_back(entity);
    entity->SetGridCell(this);
    entity->SetPosition(m_Position);
    if (!entity->IsActive())
    {
        entity->SetActive(true);
    }
}

bool GridCell::Remove(GameEntity* entity)
{
    // Find the entity in the vector using an explicit iterator type
    std::vector<GameEntity*>::iterator it = std::find(m_Entities.begin(), m_Entities.end(), entity);

    // If the entity is found, erase it
    if (it != m_Entities.end())
    {
        m_Entities.erase(it);
        return true;
    }

    return false;
}

bool GridCell::MoveEntityFrom(GameEntity* entity, EDirection direction)
{
    if (Remove(entity))
    {
        entity->SetGridCell(nullptr);
    }
    return IsEmpty();
}



const bool GridCell::IsEmpty() const
{
	return m_Entities.size() == 0;
}

const bool GridCell::CanWalkOn() const
{
    if (!m_Walkable)
    {
        return false;
    }
    return true;
}

const bool GridCell::CanSpawnOn() const
{
    if (!IsEmpty())
    {
        return false;
    }
    return true;
}

void GridCell::AssignGrid(Grid* grid)
{
    m_Grid = grid;
}

Grid* GridCell::GetGrid()
{
    return m_Grid;
}

Bush* lastBush = nullptr;

void GridCell::CheckBush()
{
    if (Game::GetInstance().GetPlayer()->GetMonster() == nullptr)
    {
        return;
    }

    if (Game::GetInstance().GetPlayer()->GetMonster()->GetHealthTrack() == nullptr)
    {
        return;
    }


    if (!IsEmpty())
    {
        if (m_Entities[0])
        {
            if (m_Entities[0]->GetEntityType() == BUSH)
            {
                Bush* bush = dynamic_cast<Bush*>(m_Entities[0]);
                if (bush && !bush->GetTriggered())
                {
                    if (bush->GetMonster())
                    {
                        if (Game::GetInstance().GetPlayer()->GetMonster()->GetHealthTrack()->GetCurrent() == 0)
                        {
                            if (lastBush != bush)
                            {
                                lastBush = bush;
                                std::cout << "Your Captured Monster is dead. Please visit the healing station." << std::endl;
                            }
                            return;
                        }

                        bush->SetTriggered(true);
                        std::cout << "Walked on monster" << std::endl;
                        Game::GetInstance().GetBattleHandler()->CreateBattle(Game::GetInstance().GetPlayer(), bush->GetMonster());
                    }
                }
            }
        }
    }
}

void GridCell::SetWalkable(bool value)
{
    m_Walkable = value;
}
