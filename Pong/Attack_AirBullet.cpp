#include "Attack_AirBullet.h"

#include <iostream>
#include "BattleMonster.h"
#include "HealthTrack.h"

using std::cout;
using std::endl;

Attack_AirBullet::Attack_AirBullet()
{
	Setup("Air Bullet", "Shoots ball of air", 5, 20, ATTACK_TYPE_WIND);
}

bool Attack_AirBullet::Activate(BattleMonster& caster, BattleMonster& target)
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
