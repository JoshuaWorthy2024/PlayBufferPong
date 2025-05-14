#include "Attack_WaterGun.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_WaterGun::Attack_WaterGun()
{
    Setup("Water Gun", "Shoots a blast of water at the target", 2, 15, ATTACK_TYPE_WATER);
}

bool Attack_WaterGun::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
    }
    return true;
}
