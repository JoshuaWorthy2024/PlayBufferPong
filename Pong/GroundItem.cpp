#include "GroundItem.h"

#include "Game.h"
#include "ItemHandler.h"

GroundItem::GroundItem(int id, int amount)
{
	m_Id = id;
	m_Amount = amount;
	m_SpriteName = Game::GetInstance().GetItemHandler()->GetSpriteName(id);
}

GroundItem::GroundItem(int id)
{
	m_Id = id;
}

void GroundItem::Draw()
{
	GameEntity::Draw();
}

void GroundItem::Update(float elapsedTime)
{
	//GameEntity::Update(elapsedTime);
}
