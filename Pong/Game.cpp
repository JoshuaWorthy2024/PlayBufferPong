#include "Ball.h"
#include "Bat.h"
#include "Config.h"
#include "Game.h"
#include "Play.h"

Game::Game()
	: m_Player1("leftpaddle", Play::Vector2D(30, DISPLAY_HEIGHT / 2), 1)
	, m_Player2("rightpaddle", Play::Vector2D(DISPLAY_WIDTH - 30, DISPLAY_HEIGHT / 2), 2)
	, m_Ball("ball", Play::Vector2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2))
{
}

Game::~Game()
{
}

bool Game::Initialise()
{
	return false;
}

void Game::Update(float elapsedTime)
{
	// Update player bats
	m_Player1.Update(elapsedTime);
	m_Player2.Update(elapsedTime);

	// Update the ball
	m_Ball.Update(elapsedTime, m_Player1, m_Player2);

	// Check if the ball goes off screen and score accordingly
	if (m_Ball.GetPosition().x < -BALL_SIZE)
	{
		// TODO: Score Player 1

		m_Ball.Reset();
	}
	else if(m_Ball.GetPosition().x > DISPLAY_WIDTH + BALL_SIZE)
	{
		// TODO: Score Player 2

		m_Ball.Reset();
	}
}

void Game::Draw()
{
	// Update game entities
	m_Player1.Draw();
	m_Player2.Draw();
	m_Ball.Draw();
}

bool Game::Deinitialise()
{
	return false;
}
