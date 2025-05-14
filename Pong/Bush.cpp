#include "Bush.h"
#include "GridCell.h"
#include "Grid.h"
#include "WildMonster.h"
#include "EntityHandler.h"

Bush::Bush(EBushType type)
{
	m_BushColor = type;
	m_EntityType = BUSH;
}

Bush::Bush(EBushType type, Play::Vector2D position)
{
	m_BushColor = type;
	m_Position = position;
}

Bush::~Bush()
{
	std::cout << "Removing bush" << std::endl;
}

void Bush::Draw()
{
	if (!m_Active)
	{
		return;
	}

	GameEntity::Draw();
}

int m_TotalFrames = 0;
const int SPEED = 300;

void Bush::Update(float elapsedTime)
{
	if (!m_Active)
		return;

	switch (m_BushColor)
	{
		case GREEN:
		{
			m_SpriteName = "bush_green";
		}

		case RED:
		{

		}
	}

	//m_Position = Play::GetMousePos();
}

void Bush::PlaceMonster(FMonsterInfo monsterInfo)
{
	monster = new WildMonster(monsterInfo);
	
	EntityHandler::GetInstance().SpawnMonster(monster, this);

	/*if (m_GridCell)
	{
		std::cout << "WildMonster spawned on: " << m_GridCell->GetRow() << ", " << m_GridCell->GetColumn() << std::endl;
	}*/
}

WildMonster* Bush::GetMonster()
{
	return monster;
}
