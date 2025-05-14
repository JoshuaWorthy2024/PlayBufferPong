#pragma once
#include "Attack.h"
class Attack_VineWhip :
    public Attack
{
public:
    Attack_VineWhip();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

