#include "StarterHouse.h"

#include "Game.h"
#include "Config.h"
#include "Player.h"
#include "GroundItem.h"
#include "CapturedMonster.h"

void StarterHouse::Draw()
{
	// Find the width/height of the sprite
	int spriteWidth = Play::GetSpriteWidth(m_SpriteName.c_str());
	int spriteHeight = Play::GetSpriteHeight(m_SpriteName.c_str());

	// Get the centered position of the sprite (top-left corner adjustment)
	Play::Vector2f centeredPos = { m_Position.x - spriteWidth * 0.5f, m_Position.y - spriteHeight * 0.5f };

	// Apply offset relative to the player
	centeredPos.x -= Game::GetInstance().GetPlayer()->GetPosition().x - (DISPLAY_WIDTH * 0.5f);
	centeredPos.y -= Game::GetInstance().GetPlayer()->GetPosition().y - (DISPLAY_HEIGHT * 0.5f);

	// Handle the animation frame update
	framePos += animationSpeed;
	if (framePos > 1.0f)
	{
		frameIndex++;
		framePos -= 1.0f;
	}

	// Draw the sprite at the newly centered and offset position
	Play::DrawSprite(m_SpriteName.c_str(), centeredPos, frameIndex);
}

void StarterHouse::Update(float elapsedTime)
{

}

StarterHouse::StarterHouse()
{
	m_SpriteName = "building_starterhouse";
}

bool StarterHouse::IsStarterHouseBoundary(int x, int y)
{
	return false;
}

void StarterHouse::Initialize()
{
	int row = GetGridCell()->GetRow();
	int col = GetGridCell()->GetColumn();
	for (int r = 0; r < 2; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			m_Boundary.push_back(Play::Vector2D(row + r, col + c));
			m_Boundary.push_back(Play::Vector2D(row - r, col - c));
			m_Boundary.push_back(Play::Vector2D(row + r, col - c));
			m_Boundary.push_back(Play::Vector2D(row - r, col + c));
		}
	}

	m_GrassStarter = new GroundItem(0, 1);
	m_FireStarter = new GroundItem(0, 1);
	m_WaterStarter = new GroundItem(0, 1);
}

bool StarterHouse::CannotWalkOn(int r, int c)
{
	for (Play::Vector2D vector : m_Boundary)
	{
		if (vector.x == r && vector.y == c)
		{
			if (GetGridCell()->GetRow() == -6 && GetGridCell()->GetColumn() == 14)
			{
				if (vector.x == -7 && vector.y == 14)
				{
					std::cout << "Trying to enter starter house" << std::endl;
					EnterStarterHouse();
					return true;
				}
			}
			return true;
		}
		else
		{
			std::cout << "(STARTER HOUSE) R: " << r << " C: " << c << " | " << GetGridCell()->GetRow() << ", " << GetGridCell()->GetColumn() << std::endl << std::endl;
		}
	}
	return false;
}

void StarterHouse::EnterStarterHouse()
{
	if (locked)
	{
		std::cout << "You already have a starter." << std::endl;
		return;
	}

	if (m_Entered)
	{
		return;
	}

	m_Entered = true;

	if (m_PreviousPosition.x != -9 && m_PreviousPosition.y != 14)
	{
		m_PreviousPosition = { Game::GetInstance().GetPlayer()->GetGridCell()->GetRow(), Game::GetInstance().GetPlayer()->GetGridCell()->GetColumn() };
	}

	std::cout << "Entering starter house..." << std::endl;

	Game::GetInstance().ActivateStarterHouseGrid();
}

void StarterHouse::Leave()
{
	if (!m_Entered)
	{
		return;
	}

	locked = true;
	m_Entered = false;
	std::cout << "leaving starter house..." << std::endl;
	Game::GetInstance().ActivateMainGrid();
}

Play::Vector2D StarterHouse::GetPreviousPosition()
{
	return m_PreviousPosition;
}

bool StarterHouse::IsStarterPokemonBall(int row, int column, Player* player)
{
	if (locked)
	{
		return false;
	}

	if (m_GrassStarter->GetGridCell()->GetRow() == row && m_GrassStarter->GetGridCell()->GetColumn() == column)
	{
		player->AddCapturedMonster(new CapturedMonster(StarterMonster_Grass, player, 1));
		Leave();
		return true;
	}

	if (m_WaterStarter->GetGridCell()->GetRow() == row && m_FireStarter->GetGridCell()->GetColumn() == column)
	{
		player->AddCapturedMonster(new CapturedMonster(StarterMonster_Water, player, 1));
		Leave();
		return true;
	}

	if (m_FireStarter->GetGridCell()->GetRow() == row && m_WaterStarter->GetGridCell()->GetColumn() == column)
	{
		player->AddCapturedMonster(new CapturedMonster(StarterMonster_Fire, player, 1));
		Leave();
		return true;
	}

	return false;
}
