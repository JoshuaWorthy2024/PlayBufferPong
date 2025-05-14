#pragma once
#include "Attack.h"
class Attack_AquaRing :
    public Attack
{
public:
    Attack_AquaRing();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

