#pragma once
#include "Attack.h"
class Attack_FlameCharge :
    public Attack
{
public:
    Attack_FlameCharge();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

