#include "Battle.h"

#include "GameEntity.h"
#include "Player.h"
#include "BattleMonster.h"
#include "Menu.h"
#include "MenuItem.h"
#include "BattleState.h"
#include "BattleMainMenuState.h"
#include "BattleFightMenuState.h"
#include "HealthTrack.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "ItemHandler.h"

using namespace std;

Battle::Battle()
{
	m_MainMenu = new Menu();
}

Battle::~Battle()
{
	cout << endl << "Deleting battle..." << endl;

	delete m_Enemy;
	delete m_Current;
	delete m_MainMenu;
	delete m_MovesMenu;
	delete m_CurrentBattleState;
}

void Battle::Start(Player* player, WildMonster* monster)
{
	m_Player = player;

	m_Current = new BattleMonster(player->GetMonster(), this);
	m_Current->SetPosition({ 250, 250 });
	m_Current->SetFrame(BattleFrame_Player);

	m_Enemy = new BattleMonster(monster, this);
	m_Enemy->SetPosition({ 720, 500 });
	m_Enemy->SetFrame(BattleFrame_Enemy);

	m_Started = true;
	m_Running = true;

	m_MainMenu->Add("1. Fight", 75, 148, 0, 0);
	m_MainMenu->Add("2. Inventory", 75, 148, 3, 40);
	m_MainMenu->Add("3. Monsters", 235, 148, 0, 0);
	m_MainMenu->Add("4. Run", 235, 148, 0, 40);
	m_MainMenu->Show(true);

	m_CurrentBattleState = new BattleMainMenuState(player, m_Current, m_Enemy, this);
}

void Battle::CaptureEnemy(InventoryItem* item)
{
	float baseChance = 0.0f;
	if (item->GetId() == 0)
	{
		baseChance = 0.2f;
	}
	else if (item->GetId() == 1)
	{
		baseChance = 0.4f;
	}
	else if (item->GetId() == 2)
	{
		baseChance = 0.7f;
	}

	int totalHealth = m_Enemy->GetTotalHealth();
	int currentHealth = m_Enemy->GetCurrentHealth();



	if (totalHealth <= 0 || currentHealth <= 0)
	{
		return;
	}
	else
	{
		// Increase chance based on how much health is missing
		float missingHealthRatio = 1.0f - static_cast<float>(currentHealth) / totalHealth;

		// You can adjust this multiplier to tune difficulty
		float bonusChance = missingHealthRatio * 0.5f;

		// Final catch chance capped to 100%
		float finalChance = std::min(1.0f, baseChance + bonusChance);

		float roll = static_cast<float>(rand()) / RAND_MAX;

		if (roll <= finalChance)
		{
			m_Player->AddCapturedMonster(new CapturedMonster(m_Enemy->GetMonsterInfo(), m_Player, 1));
			m_Enemy->GetHealthTrack()->Hurt(m_Enemy->GetHealthTrack()->GetTotal());
			std::cout << "Successfully captured monster!" << std::endl;
		}
		else
		{
			std::cout << "Failed to capture monster..." << std::endl;
		}
	}
}

void Battle::Run()
{
	if (m_Running)
	{

		if (IsFinished())
		{
			return;
		}

		if (m_Current)
		{
			m_Current->Draw();
			Play::DrawFontText("32px", "Your health: " + std::to_string(m_Current->GetCurrentHealth()) + "/" + std::to_string(m_Current->GetTotalHealth()), {BATTLE_PLAYER_HEALTH_X, BATTLE_PLAYER_HEALTH_Y});
		}
		if (m_Enemy)
		{
			m_Enemy->Draw();

			Play::DrawFontText("32px", "Enemy health: " + std::to_string(m_Enemy->GetCurrentHealth()) + "/" + std::to_string(m_Enemy->GetTotalHealth()), {BATTLE_ENEMY_HEALTH_X, BATTLE_ENEMY_HEALTH_Y});
		}

		//cout << "X: " << Play::GetMousePos().x << " | " << Play::GetMousePos().y << endl;
		
		if (m_MainMenu)
		{
			if (m_MainMenu->IsShowing())
			{
				m_MainMenu->Draw();
			}
		}

		if (m_MovesMenu)
		{
			if (m_MovesMenu->IsShowing())
			{
				m_MovesMenu->Draw();
			}
		}

		if (m_InventoryMenu)
		{
			if (m_InventoryMenu->IsShowing())
			{
				m_InventoryMenu->Draw();
			}
		}
		m_CurrentBattleState = m_CurrentBattleState->Handle();
	}
}

void Battle::ShowMainMenu()
{
	cout << "Opening main menu" << endl;
	if (m_MovesMenu)
	{
		m_MovesMenu->Show(false);
	}

	if (m_InventoryMenu)
	{
		m_InventoryMenu->Show(false);
	}

	m_MainMenu->Show(true);
}

void Battle::ShowMovesMenu()
{
	cout << "Opening battle moves menu" << endl;
	if (m_MainMenu)
	{
		m_MainMenu->Show(false);
	}
	if (m_InventoryMenu)
	{
		m_InventoryMenu->Show(false);
	}
	if (m_MovesMenu != nullptr)
	{
		delete m_MovesMenu;
		m_MovesMenu = nullptr;
	}
	m_MovesMenu = new Menu();

	m_Current->SetupMovesMenu(m_MovesMenu);
	m_MovesMenu->Show(true);
}

void Battle::ShowInventoryMenu()
{
	cout << "Opening inventory moves menu" << endl;

	if (m_MainMenu)
	{
		m_MainMenu->Show(false);
	}

	if (m_MovesMenu)
	{
		m_MovesMenu->Show(false);
	}

	if (m_InventoryMenu != nullptr)
	{
		delete m_InventoryMenu;
		m_InventoryMenu = nullptr;
	}

	m_InventoryMenu = new Menu();
	
	m_Player->GetInventory()->SetupInventoryMenu(m_InventoryMenu);
	m_InventoryMenu->Show(true);
}

bool Battle::IsFinished()
{
	if (m_Started)
	{
		if (m_Current && m_Enemy)
		{
			if (m_Current->GetHealthTrack()->GetCurrent() <= 0 || m_Enemy->GetHealthTrack()->GetCurrent() <= 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}
