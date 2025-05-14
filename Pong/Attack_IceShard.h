#pragma once
#include "Attack.h"
class Attack_IceShard :
    public Attack
{
public:
    Attack_IceShard();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

