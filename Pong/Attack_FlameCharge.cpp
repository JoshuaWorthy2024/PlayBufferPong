#include "Attack_FlameCharge.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_FlameCharge::Attack_FlameCharge()
{
    Setup("Flame Charge", "Engulfs self in fire and rams target", 4, 20, ATTACK_TYPE_FIRE);
}

bool Attack_FlameCharge::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
    }

    // Optional: You could add a caster speed buff here

    return true;
}
