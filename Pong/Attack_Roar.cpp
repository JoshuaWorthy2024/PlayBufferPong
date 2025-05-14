#include "Attack_Roar.h"

#include <iostream>
#include "BattleMonster.h"
#include "HealthTrack.h"

using std::cout;
using std::endl;

Attack_Roar::Attack_Roar()
{
	Setup("Roar", "Shouts a might roar that reduces damage", 5, 0, NO_ATTACK_TYPE);
}

bool Attack_Roar::Activate(BattleMonster& caster, BattleMonster& target)
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
