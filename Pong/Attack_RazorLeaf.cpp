#include "Attack_RazorLeaf.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_RazorLeaf::Attack_RazorLeaf()
{
    Setup("Razor Leaf", "Launches sharp-edged leaves at the target", 4, 20, ATTACK_TYPE_GRASS);
}

bool Attack_RazorLeaf::Activate(BattleMonster& caster, BattleMonster& target)
{
    int damage = GetBaseDamage();
    if (target.GetHealthTrack())
    {
        target.GetHealthTrack()->Hurt(damage);
    }
    return true;
}
