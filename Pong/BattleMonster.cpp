#include "BattleMonster.h"

#include "WildMonster.h"
#include "CapturedMonster.h"
#include "Menu.h"
#include "AttackSetHandler.h"
#include "AttackSet.h"
#include "HealthTrack.h"
#include "Battle.h"
#include "EntityHandler.h"

BattleMonster::BattleMonster(WildMonster* monster, Battle* battle)
{
	m_SpriteName = monster->GetMonsterInfo().BattleSpriteName;
	m_AttackKey = monster->GetMonsterInfo().ashc;
	std::cout << "Created Wild BattleMonster: " << m_SpriteName << std::endl;
	std::cout << "Memory: " << this << std::endl;
	m_Battle = battle;
	SetHealth(monster);
	EntityHandler::GetInstance().Destroy(monster);
	//delete m_CapturedMonster;
}

BattleMonster::BattleMonster(CapturedMonster* monster, Battle* battle)
{
	m_SpriteName = monster->GetMonsterInfo().BattleSpriteName;
	m_AttackKey = monster->GetMonsterInfo().ashc;
	std::cout << "Created Captured BattleMonster: " << m_SpriteName << std::endl;
	std::cout << "Memory: " << this << std::endl;
	m_Battle = battle;
	SetHealth(monster);
}

BattleMonster::~BattleMonster()
{
	std::cout << std::endl << "Deleting battle monster" << std::endl;
}

void BattleMonster::SetupMovesMenu(Menu* menu)
{
	AttackSetHandler::GetInstance().GetAttackSet(m_AttackKey)->ConfigureMenu(menu);
}

void BattleMonster::SetPosition(Play::Vector2D position)
{
	m_Position = position;
	std::cout << "Set position to: " << position.x << ", " << position.y << std::endl;
}

void BattleMonster::Draw()
{
	if (m_Position.x == -1 && m_Position.y == -1)
	{
		return;
	}

	// Find the width/height of the sprite
	int spriteWidth = Play::GetSpriteWidth(m_SpriteName.c_str());
	int spriteHeight = Play::GetSpriteHeight(m_SpriteName.c_str());

	// Get the centered position of the sprite (generally the origin is the top left corner)
	Play::Vector2f centeredPos = { m_Position.x - spriteWidth * 0.5f, m_Position.y - spriteHeight * 0.5f };

	// Draw the sprite at the newly centered position
	Play::DrawSprite(m_SpriteName.c_str(), centeredPos, m_Frame);
}

void BattleMonster::Update(float timeElapsed)
{

}

void BattleMonster::ActivateMove(int slot, BattleMonster& target)
{
	AttackSetHandler::GetInstance().GetAttackSet(m_AttackKey)->Activate(slot, *this, target);
	if (m_Battle)
	{
		m_Battle->SwapTurns();
	}
}

FMonsterInfo BattleMonster::GetMonsterInfo()
{
	switch (m_AttackKey)
	{
		case Ashc_Dragon:
		{
			return StarterMonster_Dragon;
		}
		case Ashc_StarterGrass:
		{
			return StarterMonster_Grass;
		}
		case Ashc_StarterWater:
		{
			return StarterMonster_Water;
		}
		case Ashc_StarterFire:
		{
			return StarterMonster_Fire;
		}
	}
}

void BattleMonster::ActivateRandom(BattleMonster& attacker, BattleMonster& target)
{
	std::shared_ptr<AttackSet> attackSet = AttackSetHandler::GetInstance().GetAttackSet(m_AttackKey);
	int slot = rand() % ((attackSet->GetAmountOfAttacks() - 1) - 0 + 1) + 0;
	attackSet->Activate(slot, attacker, target);
	if (m_Battle)
	{
		m_Battle->SwapTurns();
	}
}

const int BattleMonster::GetCurrentHealth()
{
	if (m_HealthTrack)
	{
		return m_HealthTrack->GetCurrent();
	}
	return -1;
}

const int BattleMonster::GetTotalHealth()
{
	if (m_HealthTrack)
	{
		return m_HealthTrack->GetTotal();
	}
	return -1;
}

void BattleMonster::SetHealth(WildMonster* monster)
{
	m_HealthTrack = new HealthTrack(monster->GetHealth());
}

void BattleMonster::SetHealth(CapturedMonster* monster)
{
	m_HealthTrack = monster->GetHealthTrack();
}
