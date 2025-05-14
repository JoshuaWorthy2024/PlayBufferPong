#pragma once
#include "GameEntity.h"

#include "Config.h"

class WildMonster;

enum EBushType
{
    GREEN = 0,
    RED,
};
class Bush :
    public GameEntity
{
public:
    Bush(EBushType type);
    Bush(EBushType type, Play::Vector2D position);
    ~Bush();
    void Draw();
    void Update(float elapsedTime);
    void PlaceMonster(FMonsterInfo monsterInfo);
    WildMonster* GetMonster();
    const bool GetTriggered() const { return m_Triggered; }
    void SetTriggered(bool value) { m_Triggered = value; }
private:
    int m_BushColor = -1;
    WildMonster* monster;
    bool m_Triggered = false;
};

