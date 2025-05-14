#pragma once
#include "BattleState.h"
class BattleInventoryState :
    public BattleState
{
    using BattleState::BattleState;
public:
    virtual BattleState* Handle();
    virtual void Update();
};

