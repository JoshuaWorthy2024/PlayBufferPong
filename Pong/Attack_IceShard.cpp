#include "Attack_IceShard.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_IceShard::Attack_IceShard()
{
    Setup("Ice Shard", "Launches a fast icy projectile", 4, 20, ATTACK_TYPE_WATER);
}

bool Attack_IceShard::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
    }
    return true;
}
