#include "Attack_Ember.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_Ember::Attack_Ember()
{
    Setup("Ember", "Flicks a small flame at the target", 2, 15, ATTACK_TYPE_FIRE);
}

bool Attack_Ember::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
    }
    return true;
}