#pragma once
#include "Attack.h"
class Attack_Howl :
    public Attack
{
public:
    Attack_Howl();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

