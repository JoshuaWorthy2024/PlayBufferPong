// This file's header
#include "Bat.h"

// Other includes
#include "Config.h"
#include "Play.h"


Bat::Bat(std::string inSpriteName, Play::Vector2D inPosition, int inPlayerID)
{
    m_SpriteName = inSpriteName;
    m_Position = inPosition;
    m_PlayerID = inPlayerID;
}

void Bat::Update(const float& elapsedTime)
{
    // Check keys based on player ID
    if (m_PlayerID == 1)
    {
        if (Play::KeyDown(Play::KEY_W)) m_Position.y += PLAYER_SPEED * elapsedTime;
        if (Play::KeyDown(Play::KEY_S)) m_Position.y -= PLAYER_SPEED * elapsedTime;
    }
    else if (m_PlayerID == 2)
    {
        if (Play::KeyDown(Play::KEY_UP)) m_Position.y += PLAYER_SPEED * elapsedTime;
        if (Play::KeyDown(Play::KEY_DOWN)) m_Position.y -= PLAYER_SPEED * elapsedTime;
    }

    // Adjust position
    float halfHeight = BAT_HEIGHT / 2.0f;
    m_Position.y = std::clamp(m_Position.y, halfHeight, DISPLAY_HEIGHT - halfHeight);
}
