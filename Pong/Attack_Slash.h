#pragma once
#include "Attack.h"
class Attack_Slash :
    public Attack
{
public:
    Attack_Slash();
    virtual bool Activate(BattleMonster& caster, BattleMonster& target);

private:

};

