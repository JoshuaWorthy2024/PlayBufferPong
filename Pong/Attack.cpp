#include "Attack.h"

#include "iostream"

bool Attack::Activate(BattleMonster& caster, BattleMonster& Target)
{
    std::cout << "Need activation code: " << m_Name << std::endl;
    return false;
}

void Attack::Setup(string name, string description, int cost, int baseDamage, EAttackType type)
{
    m_Name = name;
    m_Description = description;
    m_Cost = cost;
    m_BaseDamage = baseDamage;
    m_AttackType = type;
}
