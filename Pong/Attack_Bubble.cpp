#include "Attack_Bubble.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_Bubble::Attack_Bubble()
{
    Setup("Bubble", "Fires bubbles that may lower enemy speed", 3, 10, ATTACK_TYPE_WATER);
}

bool Attack_Bubble::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
        // Optional: Apply speed debuff here
    }
    return true;
}