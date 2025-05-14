#pragma once
#include "Attack.h"
class Attack_AirBullet :
    public Attack
{
public:
    Attack_AirBullet();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

