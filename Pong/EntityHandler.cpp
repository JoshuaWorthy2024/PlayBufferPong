#include "EntityHandler.h"
#include "WildMonster.h"
#include "FrameLimits.h"
#include "Grid.h"
#include "Player.h"
#include "Npc.h"

EntityHandler::EntityHandler()
{
}

EntityHandler::~EntityHandler()
{
}

/*
struct FMonsterInfo
{
	std::string MonsterName;
	std::string WildSpriteName;
	int Health = 0;
	float Speed = 0;
};
*/

void EntityHandler::Create(Play::Vector2D position, FMonsterInfo monsterInfo)
{
	m_Monsters.push_back(new WildMonster(position, monsterInfo));
}

void EntityHandler::Add(WildMonster* monster)
{
	m_Monsters.push_back(monster);
}

void EntityHandler::Add(Bush* bush)
{
	m_Bushes.push_back(bush);
}

void EntityHandler::Destroy()
{
}

void EntityHandler::UpdateAll(float elapsedTime)
{
	ProcessPendingDestruction();
	for (auto iter = m_Monsters.begin(); iter != m_Monsters.end();)
	{
		if (*iter == nullptr)  // If pointer is nullptr, erase it from the vector
		{
			iter = m_Monsters.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// Now, loop through and update the monsters
	for (std::vector<WildMonster*>::iterator iter = m_Monsters.begin(); iter != m_Monsters.end(); ++iter)
	{
		WildMonster* monster = *iter;
		if (monster->IsDestroying())
		{
			continue;
		}
		else
		{
			monster->Update(elapsedTime);
		}
	}
	for (std::vector<Bush*>::iterator iter = m_Bushes.begin(); iter != m_Bushes.end();)
	{
		if (*iter)
		{
			(*iter)->Update(elapsedTime);
			iter++;
		}
	}
	for (std::vector<Npc*>::iterator iter = m_Npcs.begin(); iter != m_Npcs.end();)
	{
		if (*iter)
		{
			(*iter)->Update(elapsedTime);
			iter++;
		}
	}
}

void EntityHandler::DrawAll()
{
	ProcessPendingDestruction();
	for (std::vector<WildMonster*>::iterator iter = m_Monsters.begin(); iter != m_Monsters.end();)
	{
		if (*iter)
		{
			WildMonster* m = *iter;
			if (m->IsDestroying())
			{
				continue;
			}
			if (m->GetGridCell())
			{
				if (m->GetGridCell()->GetGrid())
				{
					if (m->GetGridCell()->GetGrid()->IsActive())
					{
						if (m_Player)
						{
							if (m->GetGridCell()->GetGrid()->IsNearby(m_Player->GetPosition(), m->GetPosition(), DRAW_LENGTH))
							{
								m->Draw();
							}
						}
					}
				}
			}
			iter++;
		}
	}

	for (std::vector<Bush*>::iterator iter = m_Bushes.begin(); iter != m_Bushes.end();)
	{
		if (*iter)
		{
			Bush* b = *iter;
			if (b->GetGridCell())
			{
				if (b->GetGridCell()->GetGrid())
				{
					if (b->GetGridCell()->GetGrid()->IsActive())
					{
						if (m_Player)
						{
							if (b->GetGridCell()->GetGrid()->IsNearby(m_Player->GetPosition(), b->GetPosition(), DRAW_LENGTH))
							{
								b->Draw();
							}
						}
					}
				}
			}
			iter++;
		}
	}

	for (std::vector<Npc*>::iterator iter = m_Npcs.begin(); iter != m_Npcs.end();)
	{
		if (*iter)
		{
			Npc* n = *iter;
			if (n->GetGridCell())
			{
				if (n->GetGridCell()->GetGrid())
				{
					if (n->GetGridCell()->GetGrid()->IsActive())
					{
						if (m_Player)
						{
							if (n->GetGridCell()->GetGrid()->IsNearby(m_Player->GetPosition(), n->GetPosition(), DRAW_LENGTH))
							{
								n->Draw();
							}
						}
					}
				}
			}
			iter++;
		}
	}
}

const int ROWS = 5;
const int COLUMNS = 5;
const int ROW_SPACE = 31;
const int COLUMN_SPACE = 18;
const int x = 50;
const int y = 50;

void EntityHandler::SpawnBushes()
{
	for (int r = 0; r < ROWS; r++)
	{
		for (int c = 0; c < COLUMNS; c++)
		{
			Play::Vector2D pos = { x + (c * ROW_SPACE), y + (r * COLUMN_SPACE) };
			m_Bushes.push_back(new Bush(GREEN, pos));
		}
	}
}

void EntityHandler::Add(Grid* grid, int row, int column, GameEntity* entity)
{
	if (grid->Populate(row, column, entity))
	{
		if (entity)
		{
			switch (entity->GetEntityType())
			{
				case MONSTER:
				{
					m_Monsters.push_back(dynamic_cast<WildMonster*>(entity));
					break;
				}
				case BUSH:
				{
					m_Bushes.push_back(dynamic_cast<Bush*>(entity));
					break;
				}
				case NPC:
				{
					m_Npcs.push_back(dynamic_cast<Npc*>(entity));
					break;
				}
			}
		}
	}
}

void EntityHandler::SpawnMonster(WildMonster* monster, Bush* bush)
{
	monster->SetBush(bush);
	m_Monsters.push_back(monster);
}

void EntityHandler::SetMainPlayer(Player* player)
{
	m_Player = player;
}

void EntityHandler::Destroy(WildMonster* monster)
{
	if (monster->IsDestroying())
	{
		return;
	}

	monster->SetDestroying(true);
	m_PendingDeletion.push_back(monster);
}

void EntityHandler::ProcessPendingDestruction()
{
	for (WildMonster* monster : m_PendingDeletion)
	{
		// Remove from main list
		auto iter = std::find(m_Monsters.begin(), m_Monsters.end(), monster);
		if (iter != m_Monsters.end())
		{
			std::cout << "Erased " << monster << " from monster list" << std::endl;
			m_Monsters.erase(iter);
		}

		if (monster->GetBush())
		{
			Bush* bush = monster->GetBush();
			auto iter = std::find(m_Bushes.begin(), m_Bushes.end(), monster->GetBush());
			if (iter != m_Bushes.end())
			{
				std::cout << "Erased " << bush << " from bush list" << std::endl;
				m_Bushes.erase(iter);
			}
			delete bush;
		}

		delete monster;  // Safe to delete now
	}

	m_PendingDeletion.clear();  // Done
}

