#include "GameEntity.h"

void GameEntity::Draw()
{
	// Find the width/height of the sprite
	int spriteWidth = Play::GetSpriteWidth(m_SpriteName.c_str());
	int spriteHeight = Play::GetSpriteHeight(m_SpriteName.c_str());

	// Get the centered position of the sprite (generally the origin is the top left corner)
	Play::Vector2f centeredPos = { m_Position.x - spriteWidth * 0.5f, m_Position.y - spriteHeight * 0.5f };

	// Draw the sprite at the newly centered position
	Play::DrawSprite(m_SpriteName.c_str(), centeredPos, 0);
}
