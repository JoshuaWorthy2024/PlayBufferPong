#pragma once
#include "Attack.h"
class Attack_LeechSeed :
    public Attack
{
public:
    Attack_LeechSeed();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

