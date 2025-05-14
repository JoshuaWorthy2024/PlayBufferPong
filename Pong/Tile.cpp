#include "Tile.h"
#include "Game.h"
#include "Player.h"
#include "Config.h"

Tile::Tile(std::string spriteName, Play::Vector2D position)
{
	m_SpriteName = spriteName;
	m_Position = position;
}

void Tile::Draw()
{
	// Find the width/height of the sprite
	int spriteWidth = Play::GetSpriteWidth(m_SpriteName.c_str());
	int spriteHeight = Play::GetSpriteHeight(m_SpriteName.c_str());

	// Get the centered position of the sprite
	Play::Vector2f centeredPos = { m_Position.x - spriteWidth * 0.5f, m_Position.y - spriteHeight * 0.5f };

	// Apply offset relative to player
	centeredPos.x -= Game::GetInstance().GetPlayer()->GetPosition().x - (DISPLAY_WIDTH * 0.5f);
	centeredPos.y -= Game::GetInstance().GetPlayer()->GetPosition().y - (DISPLAY_HEIGHT * 0.5f);

	centeredPos.x += m_XOffset;
	centeredPos.y += m_YOffset;

	// Draw the sprite at the new offset position
	Play::DrawSprite(m_SpriteName.c_str(), centeredPos, 0);
}

bool Tile::IsVisible()
{
	int spriteID = Play::Graphics::GetSpriteId(m_SpriteName.c_str());
	Play::Vector2f spriteSize = Play::Graphics::GetSpriteSize(spriteID);
	Play::Vector2f spriteOrigin = Play::Graphics::GetSpriteOrigin(spriteID);

	Play::Point2f pos = TRANSFORM_SPACE(m_Position);

	return(pos.x + spriteSize.width - spriteOrigin.x > 0 && pos.x - spriteOrigin.x < Play::Window::GetWidth() &&
		pos.y + spriteSize.height - spriteOrigin.y > 0 && pos.y - spriteOrigin.y < Play::Window::GetHeight());
}
