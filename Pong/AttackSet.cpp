#include "AttackSet.h"

#include "vector"
#include "Attack.h"
#include "GameEntity.h"
#include "Menu.h"
#include "Config.h"
#include "Play.h"

bool AttackSet::Activate(int slot, BattleMonster& attacker, BattleMonster& target)
{
	return m_Attacks.at(slot)->Activate(attacker, target);
}



void AttackSet::ConfigureMenu(Menu* menu)
{
	int x = MENU_FIRST_X;
	int y = MENU_FIRST_Y;
	int offset = 60;
	for (int i = 0; i < GetAmountOfAttacks(); i++)
	{
		if (i == 2)
		{
			x = MENU_SECOND_X;
			y = MENU_SECOND_Y;
		}

		switch (i)
		{
			case 0:
			case 2:
				menu->Add(std::to_string(i + 1) + ") " + m_Attacks.at(i)->GetName(), x, y, 0, 0);
				break;
			case 1:
			case 3:
				menu->Add(std::to_string(i + 1) + ") " + m_Attacks.at(i)->GetName(), x, y, 0, offset);
				break;
		}
	}
}
