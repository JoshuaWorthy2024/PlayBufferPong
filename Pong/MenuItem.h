#pragma once
#include "string"
#include <Play.h>

class MenuItem
{
public:
	MenuItem(std::string text, int x, int y, int xOffset, int yOffset);
	~MenuItem();
	std::string GetText();
	void Draw();

	int GetX()
	{
		return m_X;
	}

	int GetY()
	{
		return m_Y;
	}
	
	Play::Vector2D GetVector()
	{
		return { m_X, m_Y };
	}

	Play::Vector2D GetVectorWithOffset()
	{
		return { (m_X - m_XOffset), (m_Y - m_YOffset) };
	}

private:
	int m_X;
	int m_Y;
	int m_XOffset;
	int m_YOffset;
	std::string m_Text;
};

