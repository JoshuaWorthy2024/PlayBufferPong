#include "Rock.h"
#include "Game.h"
#include "Player.h"

Rock::Rock()
{
	m_SpriteName = "player";
}

void Rock::Draw()
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

void Rock::Update(float elapsedTime)
{

}
