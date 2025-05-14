#pragma once

#include "Ball.h"
#include "Bat.h"
#include "WildMonster.h"
#include "Bush.h"
#include "EntityHandler.h"
#include "Grid.h"

class ItemHandler;
class Player;
class BattleHandler;
class Hospital;
class Shop;
class StarterHouse;

class Game
{
public:
	static Game& GetInstance()
	{
		static Game instance; // Created once, destroyed at program end
		return instance;
	}

	void OpenConsole()
	{
#ifdef _WIN32
		AllocConsole(); // Allocate a new console window
		FILE* file;
		freopen_s(&file, "CONOUT$", "w", stdout); // Redirect standard output
		freopen_s(&file, "CONOUT$", "w", stderr); // Redirect standard error
		freopen_s(&file, "CONIN$", "r", stdin);   // Redirect standard input
		std::cout << "Console initialized!\n";
#endif
	}

	bool Initialise();

	void Update(float elapsedTime);

	void Draw();

	bool Deinitialise();

	BattleHandler* GetBattleHandler()
	{
		return m_BattleHandler;
	}

	Player* GetPlayer()
	{
		return m_Player;
	}

	Hospital* GetHospital()
	{
		return m_Hospital;
	}

	Shop* GetShop()
	{
		return m_Shop;
	}

	StarterHouse* GetStarterHouse()
	{
		return m_StarterHouse;
	}
	void ActivateMainGrid();
	void ActivateHospitalGrid();
	void ActivateShopGrid();
	void ActivateStarterHouseGrid();

	Grid* GetMainGrid()
	{
		return m_Main_Grid;
	}

	Grid* GetHospitalGrid()
	{
		return m_Hospital_Grid;
	}

	ItemHandler* GetItemHandler()
	{
		return m_ItemHandler;
	}
	void BuildHospital();
	void BuildShop();
	void BuildStarterHouse();
private:
	Game();
	~Game();
	/*Bat m_Player1;
	Bat m_Player2;
	Ball m_Ball;*/
	Grid* m_Main_Grid;
	Grid* m_Hospital_Grid; // inside hospital
	Grid* m_Shop_Grid; // inside shop
	Grid* m_StarterHouse_Grid;
	Player* m_Player;
	BattleHandler* m_BattleHandler;
	Hospital* m_Hospital;
	Shop* m_Shop;
	StarterHouse* m_StarterHouse;
	ItemHandler* m_ItemHandler;
};

