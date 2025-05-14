#pragma once
#include "BattleState.h"
class BattleFightMenuState :
    public BattleState
{
    using BattleState::BattleState;
public:
    virtual BattleState* Handle();
    virtual void Update();
private:
};

