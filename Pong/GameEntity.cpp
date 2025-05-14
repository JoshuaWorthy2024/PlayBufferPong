#include "GameEntity.h"

#include "GridCell.h"
#include "Play.h"
#include "Game.h"
#include "Player.h"

void GameEntity::Draw()
{
	// Find the width/height of the sprite
	int spriteWidth = Play::GetSpriteWidth(m_SpriteName.c_str());
	int spriteHeight = Play::GetSpriteHeight(m_SpriteName.c_str());

	// Get the centered position of the sprite (top-left corner adjustment)
	Play::Vector2f centeredPos = { m_Position.x - spriteWidth * 0.5f, m_Position.y - spriteHeight * 0.5f };

	// Apply offset relative to the player
	centeredPos.x -= Game::GetInstance().GetPlayer()->GetPosition().x - (DISPLAY_WIDTH * 0.5f);
	centeredPos.y -= Game::GetInstance().GetPlayer()->GetPosition().y - (DISPLAY_HEIGHT * 0.5f);

	centeredPos.x += m_XOffset;
	centeredPos.y += m_YOffset;

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

void GameEntity::SetGridCell(GridCell* gridCell)
{
	m_GridCell = gridCell;
	if (m_EntityType == PLAYER)
	{
		if (gridCell)
		{
			std::cout << "Gridcell: " << gridCell->GetRow() << ", " << gridCell->GetColumn() << std::endl;
		}
	}
}

GridCell* GameEntity::GetGridCell()
{
	return m_GridCell;
}

bool GameEntity::IsVisible()
{
	int spriteID = Play::Graphics::GetSpriteId(m_SpriteName.c_str());
	Play::Vector2f spriteSize = Play::Graphics::GetSpriteSize(spriteID);
	Play::Vector2f spriteOrigin = Play::Graphics::GetSpriteOrigin(spriteID);

	Play::Point2f pos = TRANSFORM_SPACE(m_Position);

	return(pos.x + spriteSize.width - spriteOrigin.x > 0 && pos.x - spriteOrigin.x < Play::Window::GetWidth() &&
		pos.y + spriteSize.height - spriteOrigin.y > 0 && pos.y - spriteOrigin.y < Play::Window::GetHeight());
}
