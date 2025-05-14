#pragma once
#include "Attack.h"
class Attack_Bubble :
    public Attack
{
public:
    Attack_Bubble();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

