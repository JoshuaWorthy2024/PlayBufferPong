#pragma once
#include "Attack.h"
class Attack_WaterGun :
    public Attack
{
public:
    Attack_WaterGun();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

