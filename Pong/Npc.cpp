#include "Npc.h"

Npc::Npc(string spriteName, ETypeOfNpc type)
{
	m_SpriteName = spriteName;
	m_EntityType = NPC;
	m_NpcType = type;
}

void Npc::Draw()
{
	GameEntity::Draw();
}

void Npc::Update(float elapsedTime)
{
	switch (m_NpcType)
	{
		case NURSE:
		{

			break;
		}
	}
}
