#pragma once
#include "Attack.h"
class Attack_RazorLeaf :
    public Attack
{
public:
    Attack_RazorLeaf();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

