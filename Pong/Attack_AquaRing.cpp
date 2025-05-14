#include "Attack_AquaRing.h"

#include "BattleMonster.h"
#include "HealthTrack.h"

using std::cout;
using std::endl;

Attack_AquaRing::Attack_AquaRing()
{
	Setup("Aqua Ring", "Binds target in a ring of water", 0, 10, ATTACK_TYPE_WATER);
}

bool Attack_AquaRing::Activate(BattleMonster& caster, BattleMonster& target)
{
	cout << "Caster " << GetDescription() << " : " << caster.GetPosition().x << ", " << caster.GetPosition().y << " | Target : "
		<< target.GetPosition().x << ", " << target.GetPosition().y << endl;

	int damage = GetBaseDamage();

	// calculate here etc...

	if (target.GetHealthTrack())
	{
		target.GetHealthTrack()->Hurt(damage);
	}

	return true;
}
