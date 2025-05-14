#pragma once
#include "Attack.h"
class Attack_Growth :
    public Attack
{
public:
    Attack_Growth();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);
};

