#include "Attack_Howl.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_Howl::Attack_Howl()
{
    Setup("Howl", "Boosts user's attack power temporarily", 1, 0, NO_ATTACK_TYPE);
}

bool Attack_Howl::Activate(BattleMonster& caster, BattleMonster& target)
{
    // Optional: Apply attack buff to caster
    return true;
}
