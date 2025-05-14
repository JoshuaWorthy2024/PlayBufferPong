#include "BattleFightMenuState.h"

#include "Play.h"
#include "BattleMonster.h"
#include "Battle.h"
#include "Game.h"
#include "BattleHandler.h"
#include "BattleMainMenuState.h"

using std::cout;
using std::endl;

BattleState* BattleFightMenuState::Handle()
{
    if(m_Battle->GetPlayerTurn())
    {
        if (Play::KeyPressed(Play::KEY_BACKSPACE))
        {
            std::cout << "Exiting Inventory Menu" << std::endl;
            m_Battle->ShowMainMenu();
            return new BattleMainMenuState(parentPlayer, m_Friendly, m_Enemy, m_Battle);
        }

        if (Play::KeyPressed(Play::KEY_1) || Play::KeyPressed(Play::KEY_2) || Play::KeyPressed(Play::KEY_3) ||
            Play::KeyPressed(Play::KEY_4))
        {
            if (Play::KeyPressed(Play::KEY_1))
            {
                cout << "Casting ability 1" << endl;
                m_Friendly->ActivateMove(0, *m_Enemy);
            }
            else if (Play::KeyPressed(Play::KEY_2))
            {
                cout << "Casting ability 2" << endl;
                m_Friendly->ActivateMove(1, *m_Enemy);
            }
            else if (Play::KeyPressed(Play::KEY_3))
            {
                cout << "Casting ability 3" << endl;
                m_Friendly->ActivateMove(2, *m_Enemy);
            }
            else if (Play::KeyPressed(Play::KEY_4))
            {
                cout << "Casting ability 4" << endl;
                m_Friendly->ActivateMove(3, *m_Enemy);
            }
        }
    }
    else
    {
        cout << "Enemy move: ";
        m_Enemy->ActivateRandom(*m_Enemy, *m_Friendly);
    }
    return this;
}

void BattleFightMenuState::Update()
{
}
