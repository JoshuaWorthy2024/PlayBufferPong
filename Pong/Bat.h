#pragma once

#include "GameEntity.h"

class Bat : public GameEntity
{
public:
	Bat(std::string inSpriteName, Play::Vector2D inPosition, int inPlayerID);

	void Update(const float& elapsedTime);

	int m_PlayerID;
};

