#pragma once

class Player;
class GameEntity;
class WildMonster;
class BattleMonster;

class BattleState;
class Menu;
class Inventory;
class InventoryItem;

class Battle
{
public:
	Battle();
	~Battle();
	void Start(Player* player, WildMonster* monster);

	void CaptureEnemy(InventoryItem* item);

	void Run();
	
	Player& GetPlayer()
	{
		return *m_Player;
	}

	BattleMonster* GetCurrent()
	{
		return m_Current;
	}

	BattleMonster* GetEnemy()
	{
		return m_Enemy;
	}

	bool IsRunning()
	{
		return m_Running;
	}

	void ShowMainMenu();
	void ShowMovesMenu();
	void ShowInventoryMenu();

	void SwapTurns()
	{
		playerTurn = !playerTurn;
	}
	bool GetPlayerTurn()
	{
		return playerTurn;
	}
	bool IsFinished();
private:
	bool playerTurn = true;
	BattleMonster* m_Enemy;
	BattleMonster* m_Current;
	Player* m_Player;
	bool m_Started = false;
	bool m_Running = false;
	BattleState* m_CurrentBattleState = nullptr;
	Menu* m_MainMenu = nullptr;
	Menu* m_MovesMenu = nullptr;
	Menu* m_InventoryMenu = nullptr;
};

