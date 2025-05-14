#include "AttackSetHandler.h"

#include "Attack_Slash.h"
#include "Attack_AirBullet.h"
#include "Attack_Flamethrower.h"
#include "Attack_Roar.h"
#include "Attack_Ember.h"
#include "Attack_Smokescreen.h"
#include "Attack_FlameCharge.h"
#include "Attack_Howl.h"
#include "Attack_WaterGun.h"
#include "Attack_Bubble.h"
#include "Attack_AquaRing.h"
#include "Attack_IceShard.h"
#include "Attack_VineWhip.h"
#include "Attack_LeechSeed.h"
#include "Attack_RazorLeaf.h"
#include "Attack_Growth.h"
#include "Config.h"
#include "AttackSet.h"

AttackSetHandler::AttackSetHandler()
{
	// Create Shared ptr for moves
	std::shared_ptr<Attack_Slash> attack_Slash = std::make_shared<Attack_Slash>();
	m_SharedAttackPointers[Amn_Slash] = attack_Slash;

	std::shared_ptr<Attack_AirBullet> attack_AirBullet = std::make_shared<Attack_AirBullet>();
	m_SharedAttackPointers[Amn_AirBullet] = attack_AirBullet;

	std::shared_ptr<Attack_Flamethrower> attack_Flamethrower = std::make_shared<Attack_Flamethrower>();
	m_SharedAttackPointers[Amn_Flamethrower] = attack_Flamethrower;

	std::shared_ptr<Attack_Roar> attack_Roar = std::make_shared<Attack_Roar>();
	m_SharedAttackPointers[Amn_Roar] = attack_Roar;

	std::shared_ptr<Attack_Ember> attack_Ember = std::make_shared<Attack_Ember>();
	m_SharedAttackPointers[Amn_Ember] = attack_Ember;

	std::shared_ptr<Attack_Smokescreen> attack_Smokescreen = std::make_shared<Attack_Smokescreen>();
	m_SharedAttackPointers[Amn_Smokescreen] = attack_Smokescreen;

	std::shared_ptr<Attack_FlameCharge> attack_FlameCharge = std::make_shared<Attack_FlameCharge>();
	m_SharedAttackPointers[Amn_FlameCharge] = attack_FlameCharge;

	std::shared_ptr<Attack_Howl> attack_Howl = std::make_shared<Attack_Howl>();
	m_SharedAttackPointers[Amn_Howl] = attack_Howl;

	std::shared_ptr<Attack_WaterGun> attack_WaterGun = std::make_shared<Attack_WaterGun>();
	m_SharedAttackPointers[Amn_WaterGun] = attack_WaterGun;

	std::shared_ptr<Attack_Bubble> attack_Bubble = std::make_shared<Attack_Bubble>();
	m_SharedAttackPointers[Amn_Bubble] = attack_Bubble;

	std::shared_ptr<Attack_AquaRing> attack_AquaRing = std::make_shared<Attack_AquaRing>();
	m_SharedAttackPointers[Amn_AquaRing] = attack_AquaRing;

	std::shared_ptr<Attack_IceShard> attack_IceShard = std::make_shared<Attack_IceShard>();
	m_SharedAttackPointers[Amn_IceShard] = attack_IceShard;

	std::shared_ptr<Attack_VineWhip> attack_VineWhip = std::make_shared<Attack_VineWhip>();
	m_SharedAttackPointers[Amn_VineWhip] = attack_VineWhip;

	std::shared_ptr<Attack_LeechSeed> attack_LeechSeed = std::make_shared<Attack_LeechSeed>();
	m_SharedAttackPointers[Amn_LeechSeed] = attack_LeechSeed;

	std::shared_ptr<Attack_RazorLeaf> attack_RazorLeaf = std::make_shared<Attack_RazorLeaf>();
	m_SharedAttackPointers[Amn_RazorLeaf] = attack_RazorLeaf;

	std::shared_ptr<Attack_Growth> attack_Growth = std::make_shared<Attack_Growth>();
	m_SharedAttackPointers[Amn_Growth] = attack_Growth;

	// Create attacksets

	for (int i = AttackSetHandlerConfig_Start; i < AttackSetHandlerConfig_End; ++i)
	{
		if (i == AttackSetHandlerConfig_Start)
		{
			continue;
		}
		else if (i == AttackSetHandlerConfig_End)
		{
			break;
		}
		else
		{
			EAttackSetHandlerConfig value = static_cast<EAttackSetHandlerConfig>(i);
			m_AttackSetMap[value] = std::make_shared<AttackSet>();
		}
	}

	// testing
	Add(Ashc_Dragon, Amn_Slash);
	Add(Ashc_Dragon, Amn_AirBullet);
	Add(Ashc_Dragon, Amn_Flamethrower);
	Add(Ashc_Dragon, Amn_Roar);

	// Starter Fire
	Add(Ashc_StarterFire, Amn_Ember);
	Add(Ashc_StarterFire, Amn_FlameCharge);
	Add(Ashc_StarterFire, Amn_Howl);
	Add(Ashc_StarterFire, Amn_Smokescreen);

	// Starter Grass
	Add(Ashc_StarterGrass, Amn_Growth);
	Add(Ashc_StarterGrass, Amn_LeechSeed);
	Add(Ashc_StarterGrass, Amn_RazorLeaf);
	Add(Ashc_StarterGrass, Amn_VineWhip);

	// Starter Water
	Add(Ashc_StarterWater, Amn_Bubble);
	Add(Ashc_StarterWater, Amn_AquaRing);
	Add(Ashc_StarterWater, Amn_WaterGun);
	Add(Ashc_StarterWater, Amn_IceShard);
}

AttackSetHandler::~AttackSetHandler()
{
}

void AttackSetHandler::Add(EAttackSetHandlerConfig key, AttackMoveName move)
{
	m_AttackSetMap[key]->AddAttack(m_SharedAttackPointers[move]);
}

std::shared_ptr<AttackSet> AttackSetHandler::GetAttackSet(EAttackSetHandlerConfig key)
{
	return m_AttackSetMap[key];
}
