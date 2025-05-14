#include "MenuItem.h"

MenuItem::MenuItem(std::string text, int x, int y, int xOffset, int yOffset)
{
	m_Text = text;
	m_X = x;
	m_Y = y;
	m_XOffset = xOffset;
	m_YOffset = yOffset;
}

MenuItem::~MenuItem()
{
	std::cout << std::endl << "Deleting menu item" << std::endl;
}

std::string MenuItem::GetText()
{
	return m_Text;
}

void MenuItem::Draw()
{
	Play::DrawFontText("32px", m_Text.c_str(), GetVectorWithOffset());
}
