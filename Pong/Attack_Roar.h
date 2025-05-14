#pragma once
#include "Attack.h"
class Attack_Roar :
    public Attack
{
public:
    Attack_Roar();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

