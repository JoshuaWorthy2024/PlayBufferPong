#pragma once

#include "Ball.h"
#include "Bat.h"

class Game
{
public:
	Game();
	~Game();

	bool Initialise();

	void Update(float elapsedTime);

	void Draw();

	bool Deinitialise();

private:
	Bat m_Player1;
	Bat m_Player2;
	Ball m_Ball;
};

