#pragma once
#include "GameEntity.h"

#include "Config.h"
class Bush;



class WildMonster :
    public GameEntity
{
public:
    WildMonster(Play::Vector2D position, FMonsterInfo monsterInfo);
    WildMonster(FMonsterInfo monsterInfo);
    ~WildMonster();
    void Update(float elapsedTime);
    void Draw();

    Bush* GetBush();
    void SetBush(Bush* bush);

    const FMonsterInfo GetMonsterInfo() const
    {
        return m_MonsterInfo;
    }
    const int GetHealth() const
    {
        return m_Health;
    }
private:
    int m_Health = 0;
    float m_Speed = 0;
    int m_TotalFrames = 0;
    Bush* m_Bush = nullptr;
    bool m_Spawned = false;
    FMonsterInfo m_MonsterInfo;
};

