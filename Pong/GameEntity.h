#pragma once

#include "Play.h"
#include <string>

class GameEntity
{
public:
	// General draw to draw sprite at position
	void Draw();

	// Public getter for position
	const Play::Vector2D& GetPosition() const { return m_Position; }

protected:
	// Member variables
	Play::Vector2D m_Position;
	std::string m_SpriteName;
};

