#include "Shop.h"

#include "Game.h"
#include "Player.h"

void Shop::Draw()
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

void Shop::Update(float elapsedTime)
{
}

Shop::Shop()
{
	m_SpriteName = "building_shop";
}

bool Shop::IsShopBoundary(int x, int y)
{
	return false;
}

void Shop::Initialize()
{
	int row = GetGridCell()->GetRow();
	int col = GetGridCell()->GetColumn();
	for (int r = 0; r < 2; r++)
	{
		for (int c = 0; c < 2; c++)
		{
			m_Boundary.push_back(Play::Vector2D(row + r, col + c));
			m_Boundary.push_back(Play::Vector2D(row - r, col - c));
			m_Boundary.push_back(Play::Vector2D(row + r, col - c));
			m_Boundary.push_back(Play::Vector2D(row - r, col + c));
		}
	}
}
bool Shop::CannotWalkOn(int r, int c)
{
	for (Play::Vector2D vector : m_Boundary)
	{
		if (vector.x == r && vector.y == c)
		{
			if (GetGridCell()->GetRow() == 0 && GetGridCell()->GetColumn() == 16)
			{
				if (vector.x == -1 && vector.y == 16)
				{
					std::cout << "Trying to enter shop" << std::endl;
					EnterShop();
					return true;
				}
			}
			return true;
		}
		else
		{
			std::cout << "(SHOP) R: " << r << " C: " << c << " | " << GetGridCell()->GetRow() << ", " << GetGridCell()->GetColumn() << std::endl << std::endl;
		}
	}
	return false;
}

void Shop::EnterShop()
{
	if (m_Entered)
	{
		return;
	}

	m_Entered = true;

	m_PreviousPosition = { Game::GetInstance().GetPlayer()->GetGridCell()->GetRow(), Game::GetInstance().GetPlayer()->GetGridCell()->GetColumn() };

	std::cout << "Entering shop..." << std::endl;

	Game::GetInstance().ActivateShopGrid();
}

void Shop::Leave()
{
	if (!m_Entered)
	{
		return;
	}

	m_Entered = false;
	std::cout << "leaving shop..." << std::endl;
	Game::GetInstance().ActivateMainGrid();
}

Play::Vector2D Shop::GetPreviousPosition()
{
	return m_PreviousPosition;
}
