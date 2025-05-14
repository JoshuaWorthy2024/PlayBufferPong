#pragma once
#include <vector>
#include <memory>

class Attack;
class BattleMonster;
class Menu;

class AttackSet
{
public:
    bool Activate(int slot, BattleMonster& attacker, BattleMonster& target);

    void AddAttack(std::shared_ptr<Attack> attack)
    {
        m_Attacks.push_back(std::move(attack));
    }

    void RemoveAttack(int index)
    {
        if (index >= 0 && index < m_Attacks.size())
            m_Attacks.erase(m_Attacks.begin() + index);
    }

    void ConfigureMenu(Menu* menu);
    int GetAmountOfAttacks() const { return m_Attacks.size(); }
private:
    std::vector<std::shared_ptr<Attack>> m_Attacks;
};