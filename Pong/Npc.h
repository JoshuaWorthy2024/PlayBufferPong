#pragma once
#include "GameEntity.h"

enum ETypeOfNpc
{
    NO_TYPE_OF_NPC = 0,
	NURSE,
};

class Npc :
    public GameEntity
{
public:
    Npc(string spriteName, ETypeOfNpc type);

    void Draw();
    void Update(float elapsedTime);
    ETypeOfNpc GetNpcType()
    {
        return m_NpcType;
    }
private:
    ETypeOfNpc m_NpcType = NO_TYPE_OF_NPC;
};

