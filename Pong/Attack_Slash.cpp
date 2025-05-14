#include "Attack_Slash.h"

#include <iostream>
#include "BattleMonster.h"
#include "HealthTrack.h"

using std::cout;
using std::endl;

Attack_Slash::Attack_Slash()
{
	Setup("Slash", "Quickly swipes at a target", 0, 10, NO_ATTACK_TYPE);
}

bool Attack_Slash::Activate(BattleMonster& caster, BattleMonster& target)
{
	cout << "Caster " << GetDescription() << " : " << caster.GetPosition().x << ", " << caster.GetPosition().y << " | Target : "
		<< target.GetPosition().x << ", " << target.GetPosition().y << endl;

	int damage = GetBaseDamage();

	// calculate here etc...

	if(target.GetHealthTrack()) {
		target.GetHealthTrack()->Hurt(damage);
	}

	return true;
}
