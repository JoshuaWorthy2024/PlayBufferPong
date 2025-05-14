#include "Attack_Growth.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

Attack_Growth::Attack_Growth()
{
    Setup("Growth", "Boosts user's next attack", 1, 0, NO_ATTACK_TYPE);
}

bool Attack_Growth::Activate(BattleMonster& caster, BattleMonster& target)
{
    // Example placeholder: caster.IncreaseAttackPower(10);
    return true;
}
