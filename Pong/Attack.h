#pragma once
#include "string"
#include "Config.h"

using std::string;

class BattleMonster;

class Attack
{
public:

	virtual bool Activate(BattleMonster& caster, BattleMonster& Target);

	const string GetName() const
	{
		return m_Name;
	}

	const string GetDescription() const
	{
		return m_Description;
	}

	const int GetCost() const
	{
		return m_Cost;
	}

	const int GetBaseDamage() const
	{
		return m_BaseDamage;
	}

	const EAttackType GetAttackType() const
	{
		return m_AttackType;
	}

	bool operator==(const Attack& other) const
	{
		return GetName() == other.GetName();
	}

	void Setup(string name, string description, int cost, int baseDamage, EAttackType type);

private:
	string m_Name;
	string m_Description;
	int m_Cost;
	int m_BaseDamage;
	EAttackType m_AttackType = NO_ATTACK_TYPE;
};

