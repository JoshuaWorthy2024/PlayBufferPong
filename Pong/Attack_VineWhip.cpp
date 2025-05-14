#include "Attack_VineWhip.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_VineWhip::Attack_VineWhip()
{
    Setup("Vine Whip", "Strikes the target with whip-like vines", 2, 15, ATTACK_TYPE_GRASS);
}

bool Attack_VineWhip::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
    }
    return true;
}
