#pragma once

#include "Play.h"
#include "FrameLimits.h"
#include <string>

class GridCell;

enum ETypesOfEntities
{
	NO_ENTITY_TYPE = 0,
	PLAYER,
	BUSH,
	MONSTER,
	HOSPITAL,
	NPC,
	GROUNDITEM,
};

class GameEntity
{
public:
	// General draw to draw sprite at position
	virtual void Draw() = 0;
	virtual void Update(float elapsedTime) {}
	
	void SetPosition(Play::Vector2D position) { m_Position = position; }
	// Public getter for position
	const Play::Vector2D& GetPosition() const { return m_Position; }

	int GetFrameIndex() { return frameIndex; }

	std::string GetName() { return m_Name; }
	std::string GetSpriteName() { return m_SpriteName; }

	void SetActive(bool active) { m_Active = active; }
	const bool IsActive() const { return m_Active; }
	
	void SetGridCell(GridCell* gridCell);
	GridCell* GetGridCell();

	void SetEntityType(ETypesOfEntities type) { m_EntityType = type; }
	ETypesOfEntities GetEntityType() { return m_EntityType; }
	
	bool IsVisible();
	void SetDestroying(bool value)
	{
		m_Destroying = value;
	}
	bool IsDestroying()
	{
		return m_Destroying;
	}
	void SetXOffset(float amount)
	{
		m_XOffset = amount;
	}
	void SetYOffset(float amount)
	{
		m_YOffset = amount;
	}
protected:
	// Member variables
	bool m_Destroying = false;
	Play::Vector2D m_Position;
	std::string m_SpriteName;
	std::string m_Name;
	int frameIndex = 0;
	float framePos = 0.0f;
	float animationSpeed = 0.2f;
	bool m_Active = false;
	GridCell* m_GridCell;
	ETypesOfEntities m_EntityType = NO_ENTITY_TYPE;
	float m_XOffset = 0.0f;
	float m_YOffset = 0.0f;
};

