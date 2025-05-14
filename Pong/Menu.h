#pragma once
#include "string";

class MenuItem;

class Menu
{
public:
	~Menu();
	MenuItem* GetMenu(int id);
	void Add(std::string text, int x, int y, int xOffset, int yOffset);
	void Show(bool value)
	{
		m_Show = value;
	}
	bool IsShowing()
	{
		return m_Show;
	}
	void Draw();
private:
	bool m_Show = false;
	MenuItem* m_Menu1 = nullptr;
	MenuItem* m_Menu2 = nullptr;
	MenuItem* m_Menu3 = nullptr;
	MenuItem* m_Menu4 = nullptr;
};

