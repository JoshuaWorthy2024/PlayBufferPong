#pragma once
#include "Attack.h"
class Attack_Ember :
    public Attack
{
public:
    Attack_Ember();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

