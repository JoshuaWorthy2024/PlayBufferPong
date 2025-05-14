#include "Ball.h"
#include "Bat.h"
#include "Config.h"
#include "Game.h"
#include "Play.h"
#include "EntityHandler.h"
#include "Bush.h"
#include "Player.h"
#include "Tile.h"
#include "BattleHandler.h"
#include "Battle.h"
#include "Hospital.h"
#include "GameEntity.h"
#include "Npc.h"
#include "Shop.h"
#include "StarterHouse.h"
#include "ItemHandler.h"
#include "GroundItem.h"

/*Game::Game()
	: m_Player1("leftpaddle", Play::Vector2D(30, DISPLAY_HEIGHT / 2), 1)
	, m_Player2("rightpaddle", Play::Vector2D(DISPLAY_WIDTH - 30, DISPLAY_HEIGHT / 2), 2)
	, m_Ball("ball", Play::Vector2D(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2))
{
}*/

void Game::ActivateMainGrid()
{
	if (m_Main_Grid && m_Hospital_Grid)
	{
		if (m_Hospital_Grid->IsActive())
		{
			// leaving hospital
			m_Hospital_Grid->SetActive(false);
			m_Main_Grid->SetActive(true);

			if (m_Player->GetGridCell())
			{
				m_Player->GetGridCell()->Remove(m_Player);
			}
			Play::Vector2D lastPosition = Game::GetInstance().GetHospital()->GetPreviousPosition();
			EntityHandler::GetInstance().Add(m_Main_Grid, lastPosition.x, lastPosition.y, m_Player);

			return;
		}
		if (m_Shop_Grid->IsActive())
		{
			// leaving shop
			m_Shop_Grid->SetActive(false);
			m_Main_Grid->SetActive(true);

			if (m_Player->GetGridCell())
			{
				m_Player->GetGridCell()->Remove(m_Player);
			}
			Play::Vector2D lastPosition = Game::GetInstance().GetShop()->GetPreviousPosition();
			EntityHandler::GetInstance().Add(m_Main_Grid, lastPosition.x, lastPosition.y, m_Player);

			return;
		}
		if (m_StarterHouse_Grid->IsActive())
		{
			// leaving shop
			m_StarterHouse_Grid->SetActive(false);
			m_Main_Grid->SetActive(true);

			if (m_Player->GetGridCell())
			{
				m_Player->GetGridCell()->Remove(m_Player);
			}
			Play::Vector2D lastPosition = Game::GetInstance().GetShop()->GetPreviousPosition();
			EntityHandler::GetInstance().Add(m_Main_Grid, lastPosition.x, lastPosition.y, m_Player);

			return;
		}
		else if (!m_Main_Grid->IsActive() && !m_Hospital_Grid->IsActive())
		{
			// start of program
			m_Main_Grid->SetActive(true);
		}
	}
}

void Game::ActivateHospitalGrid()
{
	m_Main_Grid->SetActive(false);
	m_Shop_Grid->SetActive(false);
	m_Hospital_Grid->SetActive(true);
	m_StarterHouse_Grid->SetActive(false);
	m_Player->GetGridCell()->Remove(m_Player);
	m_Hospital_Grid->SetOrigin(Game::GetInstance().GetPlayer());
}

void Game::ActivateShopGrid()
{
	m_Main_Grid->SetActive(false);
	m_Hospital_Grid->SetActive(false);
	m_StarterHouse_Grid->SetActive(false);
	m_Shop_Grid->SetActive(true);
	m_Player->GetGridCell()->Remove(m_Player);
	m_Shop_Grid->SetOrigin(Game::GetInstance().GetPlayer());
}

void Game::ActivateStarterHouseGrid()
{
	m_Main_Grid->SetActive(false);
	m_Hospital_Grid->SetActive(false);
	m_Shop_Grid->SetActive(false);
	m_StarterHouse_Grid->SetActive(true);
	m_Player->GetGridCell()->Remove(m_Player);
	m_Shop_Grid->SetOrigin(Game::GetInstance().GetPlayer());
}

void Game::BuildHospital()
{
	m_Hospital_Grid->CreateTile("tile_hospitalentrance", 0, 0, true);

	int counter = 1;

	// Setting up tiles for Hospital
	for (; counter < 6; counter++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_Hospital_Grid->CreateTile("tile_hospitalfloor", counter, i, true);
			m_Hospital_Grid->CreateTile("tile_hospitalfloor", counter, i * -1, true);
		}
	}

	// Setting up Objects in Hospital Room
	m_Hospital_Grid->CreateTile("chair_right", 3, -3, false);
	m_Hospital_Grid->CreateTile("bluetable", 3, -2, false);

	Tile* hospitalCounter = m_Hospital_Grid->CreateTile("hospital_counter", 5, 0, false);

	if (hospitalCounter)
	{
		hospitalCounter->SetYOffset(-5);
	}

	m_Hospital_Grid->CreateTile("flowerpot", 1, -3, false);
	m_Hospital_Grid->CreateTile("flowerpot", 1, 3, false);
	m_Hospital_Grid->CreateTile("flowerpot", 5, -3, false);
	m_Hospital_Grid->CreateTile("flowerpot", 5, 3, false);

	Npc* nurse = new Npc("nurse", NURSE);
	nurse->SetYOffset(3);
	EntityHandler::GetInstance().Add(m_Hospital_Grid, 5, 0, nurse);
}

void Game::BuildShop()
{
	m_Shop_Grid->CreateTile("tile_hospitalentrance", 0, 0, true);

	int counter = 1;

	// Setting up tiles for Hospital
	for (; counter < 6; counter++)
	{
		for (int i = 0; i < 4; i++)
		{
			m_Shop_Grid->CreateTile("tile_hospitalfloor", counter, i, true);
			m_Shop_Grid->CreateTile("tile_hospitalfloor", counter, i * -1, true);
		}
	}

	m_Shop_Grid->CreateTile("shop_table", 5, -2, false);
	m_Shop_Grid->CreateTile("shop_table", 5, 0, false);
	m_Shop_Grid->CreateTile("shop_table", 5, 2, false);

	m_ItemHandler->AddGroundItem(0, 1, m_Shop_Grid, 5, -2);
	m_ItemHandler->AddGroundItem(1, 1, m_Shop_Grid, 5, 0);
	m_ItemHandler->AddGroundItem(2, 1, m_Shop_Grid, 5, 2);
}

void Game::BuildStarterHouse()
{
	m_StarterHouse_Grid->CreateTile("tile_hospitalentrance", 0, 0, true);

	int counter = 1;

	// Setting up tiles for Starter House
	for (; counter < 6; counter++)
	{
		for (int i = 0; i < 6; i++)
		{
			m_StarterHouse_Grid->CreateTile("tile_hospitalfloor", counter, i, true);
			m_StarterHouse_Grid->CreateTile("tile_hospitalfloor", counter, i * -1, true);
		}
	}

	m_StarterHouse_Grid->CreateTile("shop_table", 5, -2, false);
	m_StarterHouse_Grid->CreateTile("shop_table", 5, 0, false);
	m_StarterHouse_Grid->CreateTile("shop_table", 5, 2, false);

	m_ItemHandler->AddGroundItem(m_StarterHouse->GetGrassStarter(), m_StarterHouse_Grid, 5, -2);
	m_ItemHandler->AddGroundItem(m_StarterHouse->GetFireStarter(), m_StarterHouse_Grid, 5, 0);
	m_ItemHandler->AddGroundItem(m_StarterHouse->GetWaterStarter(), m_StarterHouse_Grid, 5, 2);
}

Game::Game()
{

}
Game::~Game()
{

}

int RandomNumber(int min, int max)
{
	return rand() % (max - min) + 1;
}

bool Game::Initialise()
{
	srand(time(0));
	OpenConsole();

	m_BattleHandler = new BattleHandler();
	m_ItemHandler = new ItemHandler();

	m_Main_Grid = new Grid(GRID_ROW, GRID_COLUMN, GRID_START_X, GRID_START_Y, GRID_SPACE_X, GRID_SPACE_Y, "main", GRID_MAIN);
	m_Main_Grid->SetOrigin(0, 0);
	m_Main_Grid->Initialize();

	m_Hospital_Grid = new Grid(GRID_ROW, GRID_COLUMN, GRID_START_X, GRID_START_Y, GRID_SPACE_X, GRID_SPACE_Y, "hospital", GRID_HOSPITAL);
	m_Hospital_Grid->SetOrigin(1, 0);
	m_Hospital_Grid->Initialize();

	m_Shop_Grid = new Grid(GRID_ROW, GRID_COLUMN, GRID_START_X, GRID_START_Y, GRID_SPACE_X, GRID_SPACE_Y, "shop", GRID_SHOP);
	m_Shop_Grid->SetOrigin(1, 0);
	m_Shop_Grid->Initialize();

	m_StarterHouse_Grid = new Grid(GRID_ROW, GRID_COLUMN, GRID_START_X, GRID_START_Y, GRID_SPACE_X, GRID_SPACE_Y, "starter_house", GRID_SHOP);
	m_StarterHouse_Grid->SetOrigin(1, 0);
	m_StarterHouse_Grid->Initialize();
	
	m_Player = new Player();
	
	int counter = 0;

	EntityHandler::GetInstance().SetMainPlayer(m_Player);
	EntityHandler::GetInstance().Add(m_Main_Grid, 0, 0, m_Player);

	m_Hospital = new Hospital();
	m_Shop = new Shop();
	m_StarterHouse = new StarterHouse();

	m_Main_Grid->Populate(0, 7, m_Hospital);
	m_Main_Grid->Populate(0, 16, m_Shop);
	m_Main_Grid->Populate(-6, 14, m_StarterHouse);

	m_Hospital->Initialize();
	m_Shop->Initialize();
	m_StarterHouse->Initialize();

	for (int r = (GRID_ROW * -1); r < GRID_ROW; r++)
	{
		for (int c = (GRID_COLUMN * -1); c < GRID_COLUMN; c++)
		{
			m_Main_Grid->CreateTile("patch", r, c, true);
		}
	}

	for (int r = (GRID_ROW * -1); r < GRID_ROW; r++)
	{
		for (int c = (GRID_COLUMN * -1); c < GRID_COLUMN; c++)
		{
			if (m_Main_Grid->IsNearby(*m_Hospital->GetGridCell(), r, c, 6, 6))
			{
				continue;
			}
			if (m_Main_Grid->IsNearby(*m_Shop->GetGridCell(), r, c, 6, 6))
			{
				continue;
			}
			if (m_Main_Grid->IsNearby(*m_StarterHouse->GetGridCell(), r, c, 6, 6))
			{
				continue;
			}
			if (RandomNumber(0, (GRID_ROW * 3)) <= GRID_ROW)
			{
				if (counter < 6)
				{
					switch (RandomNumber(0, 2))
					{
						case 1: // nothing
						{
							Bush* bush = new Bush(GREEN);
							EntityHandler::GetInstance().Add(m_Main_Grid, r, c, bush);
							counter++;
							break;
						}
						case 2: // spawn m_CapturedMonster
						{
							Bush* bush = new Bush(GREEN);
							EntityHandler::GetInstance().Add(m_Main_Grid, r, c, bush);
							bush->PlaceMonster(StarterMonster_Dragon);
							counter++;
							break;
						}
					}
				}
				else
				{
					counter = 0;
					r++;
				}
			}
		}
	}

	ActivateMainGrid();
	BuildHospital();
	BuildShop();
	BuildStarterHouse();
	return false;
}

void Game::Update(float elapsedTime)
{
	if (m_BattleHandler->GetBattle())
	{
		if (m_BattleHandler->GetBattle() && m_BattleHandler->GetBattle()->IsFinished())
		{
			m_BattleHandler->SetBattle(nullptr); // This automatically deletes the Battle instance
		}
	}
	else
	{
		if (m_Main_Grid->IsActive())
		{
			m_Player->Update(elapsedTime);
			EntityHandler::GetInstance().UpdateAll(elapsedTime);
			if (m_Hospital)
			{
				m_Hospital->Update(elapsedTime);
			}
		}

		if (m_Hospital_Grid->IsActive())
		{
			m_Player->Update(elapsedTime);
			EntityHandler::GetInstance().UpdateAll(elapsedTime);
		}

		if (m_Shop_Grid->IsActive())
		{
			m_Player->Update(elapsedTime);
			EntityHandler::GetInstance().UpdateAll(elapsedTime);
		}

		if (m_StarterHouse->IsActive())
		{
			m_Player->Update(elapsedTime);
			EntityHandler::GetInstance().UpdateAll(elapsedTime);
		}

	}
}

void Game::Draw()
{
	if (m_BattleHandler->GetBattle())
	{
		m_BattleHandler->GetBattle()->Run();
	}
	else
	{
		if (m_Main_Grid->IsActive())
		{
			m_Main_Grid->DrawTiles(m_Player);
			m_Player->Draw();
			EntityHandler::GetInstance().DrawAll();
			m_Hospital->Draw();
			m_Shop->Draw();
			m_StarterHouse->Draw();
		}
		if (m_Hospital_Grid->IsActive())
		{
			m_Hospital_Grid->DrawTiles(m_Player);
			m_Player->Draw();
			EntityHandler::GetInstance().DrawAll();
		}
		if (m_Shop_Grid->IsActive())
		{
			m_Shop_Grid->DrawTiles(m_Player);
			m_Player->Draw();
			EntityHandler::GetInstance().DrawAll();
		}

		if (m_StarterHouse_Grid->IsActive())
		{
			m_StarterHouse_Grid->DrawTiles(m_Player);
			m_Player->Draw();
			EntityHandler::GetInstance().DrawAll();
		}

		m_ItemHandler->DrawAll();
	}
}

/*
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
}*/

bool Game::Deinitialise()
{
	return false;
}
