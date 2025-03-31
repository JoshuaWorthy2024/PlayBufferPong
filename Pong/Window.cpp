#define PLAY_IMPLEMENTATION

// Includes
#include "Config.h"
#include "Game.h"
#include "Play.h"

// Globals
Game gameInstance;

void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	// Create the PlayBuffer window
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);

	// Initialise the game instance
	gameInstance.Initialise();
}

bool MainGameUpdate(float elapsedTime )
{
	// Clear the draw buffer
	Play::ClearDrawingBuffer( Play::cBlack );

	// Update and draw the game
	gameInstance.Update(elapsedTime);
	gameInstance.Draw();

	// Present the draw buffer to the screen
	Play::PresentDrawingBuffer();	

	return Play::KeyDown( KEY_ESCAPE );
}

int MainGameExit( void )
{
	// Destroy the PlayerBuffer window
	Play::DestroyManager();

	return PLAY_OK;
}

