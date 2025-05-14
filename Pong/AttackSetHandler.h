#pragma once

#include "Config.h"
#include "memory"
#include "map"

class AttackSet;
class Attack;

class AttackSetHandler
{
public:
	static AttackSetHandler& GetInstance()
	{
		static AttackSetHandler instance; // Created once, destroyed at program end
		return instance;
	}


	void Add(EAttackSetHandlerConfig key, AttackMoveName move);
	std::shared_ptr<AttackSet> GetAttackSet(EAttackSetHandlerConfig key);

private:
	AttackSetHandler();
	~AttackSetHandler();
	std::map<EAttackSetHandlerConfig, std::shared_ptr<AttackSet>> m_AttackSetMap;
	std::map<AttackMoveName, std::shared_ptr<Attack>> m_SharedAttackPointers;

	// map where key is string, value is vector
};

