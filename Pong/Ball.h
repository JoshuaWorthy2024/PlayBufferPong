#pragma once

#include "GameEntity.h"

// Forward declarations
class Bat;

class Ball : public GameEntity
{
public:
	// Parameterised constructor
	Ball(std::string inSpriteName, Play::Vector2D inPosition);

	// Updates position of the ball
	void Update(const float& elapsedTime, const Bat& inPlayer1, const Bat& inPlayer2);

	// Resets position of the ball
	void Reset();

private:
	// Check for AABB collision
	bool CheckCollision(const Play::Vector2f& aPos, float aWidth, float aHeight,
						const Play::Vector2f& bPos, float bWidth, float bHeight);

	// Applies a varied level of bounce in the Y axis to the ball
	void ApplyBounceYVariation(const Bat& bat);

	Play::Vector2f m_Velocity;

};

