#include "Attack_Flamethrower.h"

#include <iostream>
#include "BattleMonster.h"
#include "HealthTrack.h"

using std::cout;
using std::endl;

Attack_Flamethrower::Attack_Flamethrower()
{
	Setup("Flamethrower", "Shoots a stream of flame", 5, 50, ATTACK_TYPE_FIRE);
}

bool Attack_Flamethrower::Activate(BattleMonster& caster, BattleMonster& target)
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
