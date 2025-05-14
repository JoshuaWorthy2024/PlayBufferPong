#pragma once

class Player;
class BattleMonster;
class Battle;

class BattleState
{
public:
	BattleState(Player* player, BattleMonster* friendly, BattleMonster* enemy, Battle* battle);
	virtual BattleState* Handle() = 0;
	virtual void Update() = 0;
protected:
	Player* parentPlayer;
	BattleMonster* m_Friendly;
	BattleMonster* m_Enemy;
	Battle* m_Battle = nullptr;
};

