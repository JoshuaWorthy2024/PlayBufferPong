#pragma once
#include "Attack.h"
class Attack_Smokescreen :
    public Attack
{
public:
    Attack_Smokescreen();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

