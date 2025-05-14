#include "Menu.h"

#include "MenuItem.h"

Menu::~Menu()
{
    std::cout << std::endl << "Deleting menu" << std::endl;
    delete m_Menu1;
    delete m_Menu2;
    delete m_Menu3;
    delete m_Menu4;
}

MenuItem* Menu::GetMenu(int id)
{
    switch (id)
    {
        case 1:
        {
            return m_Menu1;
        }
        case 2:
        {
            return m_Menu2;
        }
        case 3:
        {
            return m_Menu3;
        }
        case 4:
        {
            return m_Menu4;
        }
    }
    return nullptr;
}

void Menu::Add(std::string text, int x, int y, int xOffset, int yOffset)
{
    if (m_Menu1 == nullptr)
    {
        m_Menu1 = new MenuItem(text, x, y, xOffset, yOffset);
        return;
    }

    if (m_Menu2 == nullptr)
    {
        m_Menu2 = new MenuItem(text, x, y, xOffset, yOffset);
        return;
    }

    if (m_Menu3 == nullptr)
    {
        m_Menu3 = new MenuItem(text, x, y, xOffset, yOffset);
        return;
    }

    if (m_Menu4 == nullptr)
    {
        m_Menu4 = new MenuItem(text, x, y, xOffset, yOffset);
        return;
    }
}

void Menu::Draw()
{
    if (m_Show)
    {
        if (m_Menu1)
        {
            m_Menu1->Draw();
        }

        if (m_Menu2)
        {
            m_Menu2->Draw();
        }

        if (m_Menu3)
        {
            m_Menu3->Draw();
        }

        if (m_Menu4)
        {
            m_Menu4->Draw();
        }
    }
}
