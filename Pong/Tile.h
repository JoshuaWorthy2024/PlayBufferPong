#pragma once
#include "Play.h"

class Tile
{
public:
	Tile(std::string spriteName, Play::Vector2D position);

	Play::Vector2D GetPosition() { return m_Position; }
	void Draw();
	bool IsVisible();
	void SetXOffset(float amount)
	{
		m_XOffset = amount;
	}
	void SetYOffset(float amount)
	{
		m_YOffset = amount;
	}
private:
	Play::Vector2D m_Position;
	std::string m_SpriteName;
	float m_XOffset = 0.0f;
	float m_YOffset = 0.0f;
};

