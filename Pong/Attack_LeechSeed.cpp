#include "Attack_LeechSeed.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_LeechSeed::Attack_LeechSeed()
{
    Setup("Leech Seed", "Plants a seed that drains target's health over time", 3, 5, ATTACK_TYPE_GRASS);
}

bool Attack_LeechSeed::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
        // Optionally: heal caster or apply drain effect over turns
    }
    return true;
}
