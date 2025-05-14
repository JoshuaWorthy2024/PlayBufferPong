#pragma once
#include "BattleState.h"
class BattleMainMenuState :
    public BattleState
{
    using BattleState::BattleState;
public:
    virtual BattleState* Handle();
    virtual void Update();
};

