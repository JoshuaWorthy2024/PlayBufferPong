#include "WildMonster.h"

#include "Bush.h"

WildMonster::WildMonster(Play::Vector2D position, FMonsterInfo monsterInfo)
{
	m_Position = position;
	m_Name = monsterInfo.MonsterName;
	m_Health = monsterInfo.Health;
	m_SpriteName = monsterInfo.WildSpriteName;
	m_TotalFrames = monsterInfo.Frames;
	m_EntityType = MONSTER;
	m_MonsterInfo = monsterInfo;
}

WildMonster::WildMonster(FMonsterInfo monsterInfo)
{
	m_Name = monsterInfo.MonsterName;
	m_Health = monsterInfo.Health;
	m_SpriteName = monsterInfo.WildSpriteName;
	m_TotalFrames = monsterInfo.Frames;
	m_EntityType = MONSTER;
	m_MonsterInfo = monsterInfo;
}

WildMonster::~WildMonster()
{
	std::cout << std::endl << "Deleting wildmonster" << std::endl;
}

void WildMonster::Update(float elapsedTime)
{
	//m_Position = Play::GetMousePos();
}

int lastFrame = -1;
int nameOffsetY = -5;
void WildMonster::Draw()
{
	if (m_Bush)
	{
		return;
	}
	GameEntity::Draw();
	if (lastFrame != frameIndex)
	{
		lastFrame++;
	}

	//Play::DrawFontText("32px", m_Name, { m_Position.x, (m_Position.y - (nameOffsetY + lastFrame)) }, Play::CENTRE);

	if (frameIndex == m_TotalFrames)
	{
		frameIndex = 0;
		lastFrame = -1;
	}
}

Bush* WildMonster::GetBush()
{
	return m_Bush;
}

void WildMonster::SetBush(Bush* bush)
{
	m_Bush = bush;
	m_Position = m_Bush->GetPosition();
	m_Active = true;
}
