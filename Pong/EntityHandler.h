#pragma once
#include "WildMonster.h"
#include "Bush.h"
#include "Grid.h"

class Player;
class Npc;

class EntityHandler
{
public:
	static EntityHandler& GetInstance()
	{
		static EntityHandler instance; // Created once, destroyed at program end
		return instance;
	}

	// Redoing this part
	void Create(Play::Vector2D position, FMonsterInfo monsterInfo);
	void Add(WildMonster* monster);
	void Add(Bush* bush);
	void Destroy();
	void UpdateAll(float elapsedTime);
	void DrawAll();

	void SpawnBushes();
	// May redo this, just testing for now
	void Add(Grid* grid, int row, int column, GameEntity* entity);
	void SpawnMonster(WildMonster* monster, Bush* bush);
	void SetMainPlayer(Player* player);
	void Destroy(WildMonster* monster);
private:

	EntityHandler();
	~EntityHandler();
	void ProcessPendingDestruction();
	// May do something differently, but would like to have them all organized
	std::vector<WildMonster*> m_Monsters;
	std::vector<WildMonster*> m_PendingDeletion;
	std::vector<Bush*> m_Bushes;
	std::vector<Npc*> m_Npcs;
	Player* m_Player;
};

